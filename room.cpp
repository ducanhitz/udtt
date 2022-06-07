/*Chương trình mô phỏng một số hoạt động cơ bản của đồ dùng trong phòng cá nhân (Có sử dụng mô hình chiếu sáng Blinn-Phong)*/

#include "Angel.h" /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/
#include <iostream>

// remember to prototype
void generateGeometry(void);
void initGPUBuffers(void);
void shaderSetup(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

typedef vec4 point4;
typedef vec4 color4;
using namespace std;

#define PI 3.1415926535897932384626433832795 //Gán số pi

//Khai báo một số biến để vẽ hình chóp cụt
float h = 0.5, bk1 = 0.2, bk2 = 0.4;
float step = 2 * PI / 8;
const GLfloat dr = 5.0 * DegreesToRadians;

// Số các đỉnh của các tam giác
const int NumPoints = 36;
// Số các đỉnh của hình chóp cụt
const int NumPoints_1 = 84;

point4 points[NumPoints + NumPoints_1]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[NumPoints + NumPoints_1]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
vec3 normals[NumPoints + NumPoints_1];  /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/

point4 vertices[24];     /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/

GLuint program;

GLfloat px = 4, py = 0.0, pz = 0.0;

mat4 model;
GLuint model_loc;
mat4 projection;
GLuint projection_loc;
mat4 view;
GLuint view_loc;

/* Khởi tạo các tham số chiếu sáng - tô bóng*/
point4 light_position(0.0, 0.0, 1.0, 0.0);
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

color4 material_ambient(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse(1.0, 0.0, 0.0, 1.0);
color4 material_specular(1.0, 0.0, 0.0, 1.0);
float material_shininess = 100.0;

color4 ambient_product = light_ambient * material_ambient;
color4 diffuse_product = light_diffuse * material_diffuse;
color4 specular_product = light_specular * material_specular;

void initCube()
{
    // Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
    vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
    vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
    vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
    vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
    vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
    vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
    vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
    vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

    // Gán giá trị tọa độ vị trí cho các đỉnh của hình chóp cụt
    for (int i = 8; i <= 15; i++)
    {
        vertices[i] = point4(bk1 * cos(i * step), bk1 * sin(i * step), -h / 2, 1.0);
        vertices[i + 8] = point4(bk2 * cos(i * step), bk2 * sin(i * step), h / 2, 1.0);
    }

    // Gán giá trị màu sắc cho các đỉnh của hình lập phương
    vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
    vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
    vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
    vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
    vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
    vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
    vertex_colors[6] = color4(1.0, 0.5, 0.0, 1.0); // orange
    vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan
}

int Index = 0;
void quad(int a, int b, int c, int d, int e) /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
{
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];
    vec3 normal = normalize(cross(u, v));

    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[a];
    Index++;
    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[b];
    Index++;
    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[c];
    Index++;
    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[a];
    Index++;
    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[c];
    Index++;
    normals[Index] = normal;
    colors[Index] = vertex_colors[e];
    points[Index] = vertices[d];
    Index++;
}

void makeColorCube(void)
{
    //Sinh các mặt của hình lập phương
    quad(1, 0, 3, 2, 1);
    quad(2, 3, 7, 6, 1);
    quad(3, 0, 4, 7, 1);
    quad(6, 5, 1, 2, 1);
    quad(4, 5, 6, 7, 1);
    quad(5, 4, 0, 1, 1);

    // Sinh các mặt bên hình chóp cut
    quad(8, 9, 17, 16, 1);
    quad(9, 10, 18, 17, 1);
    quad(10, 11, 19, 18, 1);
    quad(11, 12, 20, 19, 1);
    quad(12, 13, 21, 20, 1);
    quad(13, 14, 22, 21, 1);
    quad(14, 15, 23, 22, 1);
    quad(15, 8, 16, 23, 1);

    // Sinh hai mặt hình chóp cụt
    quad(8, 9, 10, 11, 1);
    quad(8, 11, 12, 13, 1);
    quad(8, 13, 14, 15, 1);
    quad(16, 17, 18, 19, 1);
    quad(16, 19, 20, 21, 1);
    quad(16, 21, 22, 23, 1);
}
void generateGeometry(void)
{
    initCube();
    makeColorCube();
}

void initGPUBuffers(void)
{
    // Tạo một VAO - vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Tạo và khởi tạo một buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);
}

void shaderSetup(void)
{
    // Nạp các shader và sử dụng chương trình shader
    program = InitShader("vshader1.glsl", "fshader1.glsl"); // hàm InitShader khai báo trong Angel.h
    glUseProgram(program);

    // Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
    GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc_vPosition);
    glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc_vColor);
    glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

    GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(loc_vNormal);
    glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors)));

    glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
    glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
    glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
    glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
    glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

    model_loc = glGetUniformLocation(program, "Model");
    projection_loc = glGetUniformLocation(program, "Projection");
    view_loc = glGetUniformLocation(program, "View");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); /* Thiết lập màu trắng là màu xóa màn hình*/
}

void MakeColor(double x, double y, double z, double t) //To mau cho vat
{
    material_diffuse = vec4(x, y, z, t); // mau vat
    diffuse_product = light_diffuse * material_diffuse;
    glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
}

mat4 Ban_view;
mat4 CuaTu_view;
mat4 HopBan_view;
mat4 Den_view;
mat4 Ghe_view;
mat4 Cua_view;
GLfloat xphong = 0.0, yphong = 0.0, zphong = 0.0, cua = 180.0, cuatu = 0.0, zhopban = 0.0, d1 = 0.0, d2 = 0.0, xghe = 0.0, zghe = 0.0, xden = 0.0;

//Bàn

//Chan ban
void Chan(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.05, 0.5, 0.4);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Cua tu
void CuaTu()
{
    //Than cua
    MakeColor(0, 0.5, 0, 1);
    CuaTu_view = Translate(0.45, -0.05, 0.225) * RotateY(cuatu) * Translate(-0.15, -0.02, -0.025);

    mat4 m = Scale(0.3, 0.3, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * CuaTu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    //Num cua
    MakeColor(1.0, 0.2, 0.2, 1);
    m = Translate(-0.1, 0, 0.015) * Scale(0.03, 0.07, 0.02);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * CuaTu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Hop ban
void HopBan(GLfloat x, GLfloat y, GLfloat z)
{
    HopBan_view = Translate(0.0, 0.0, zhopban) * Translate(x, y, z);
    MakeColor(0, 0.5, 0, 1);

    //Mat Truoc
    mat4 m = Translate(0.0, 0.0, 0.165) * Scale(0.3, 0.15, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    //Mat sau
    m = Translate(0.0, 0.0, -0.165) * Scale(0.3, 0.1, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat ben
    m = Translate(0.135, 0.0, 0.0) * Scale(0.03, 0.1, 0.3);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat ben
    m = Translate(-0.135, 0.0, 0.0) * Scale(0.03, 0.1, 0.3);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat day
    MakeColor(0.5, 0.2, 0, 1);
    m = Translate(0.0, -0.039, 0.0) * Scale(0.3, 0.02, 0.3);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Num
    MakeColor(1.0, 0.2, 0.2, 1);
    m = Translate(0.0, 0.015, 0.18) * Scale(0.05, 0.02, 0.02);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * HopBan_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Ban()
{
    Ban_view = Translate(1.25, -0.4, -0.12) * Scale(0.8, 0.8, 0.7) * RotateY(-90);
    MakeColor(0.5, 0.5, 0.9, 1);

    Chan(-0.475, 0.0, 0.0);
    Chan(0.125, 0.0, 0.0);
    Chan(0.475, 0.0, 0.0);

    //Mat sau
    mat4 m = Translate(0.0, 0.0, -0.22) * Scale(1.0, 0.5, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat Ban
    m = Translate(0.0, 0.275, 0.0) * Scale(1.1, 0.05, 0.45);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat tu
    m = Translate(0.3, -0.225, 0.0) * Scale(0.3, 0.05, 0.4);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    //Mat tu
    m = Translate(0.3, 0.1, 0.0) * Scale(0.3, 0.05, 0.4);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ban_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    CuaTu();
    HopBan(0.3, 0.17, 0.03);
}

//=============================================================
//Đèn

//Thân
void ThanDen(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.05, 0.1, 0.05);

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Den_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Đế
void ChanDen(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.5, 0.3, 1);
    mat4 m = Translate(x, y, z) * Scale(0.5, 0.1, 0.5);

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Den_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
//Đầu
void DauDen(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0.8, 0.5, 0, 1);
    mat4 m = Translate(x, y, z) * Scale(0.2, 0.1, 0.1);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Den_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(x, y, z) * Translate(0.2, 0.0, 0.0) * Scale(0.5, 0.35, 0.35) * RotateY(90);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Den_view * m);
    glDrawArrays(GL_TRIANGLES, NumPoints, NumPoints_1 + NumPoints);
}

void Den()
{
    float n = 0.0;
    Den_view = Translate(1.35, -0.15, -0.4) * Scale(0.2, 0.2, 0.2) * RotateY(-90) * RotateY(d1);
    ChanDen(0, -0.025, 0);
    ThanDen(0, n += 0.1, 0);
    ThanDen(0, n += 0.1, 0);

    ThanDen(0, 0, 0);
    Den_view = Den_view * Translate(0.0, n += 0.07, 0.0) * RotateZ(d2);
    for (int i = 0; i < 10; i++)
    {
        ThanDen(0, 0, 0);
        Den_view = Den_view * Translate(0.0, 0.07, 0.0) * RotateZ(d2);
    }
    ThanDen(0, 0, 0);
    Den_view = Den_view * Translate(0.0, 0.07, 0.0);
    DauDen(0, 0.0, 0);
}
//=======================================================================

//Ghế

//Lung ghe (Hơi cong về phía sau)
void LungGhe(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(-0.2, y, -0.2 - z) * RotateX(x) * Scale(0.05, 0.2, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0, y, -0.2 - z) * RotateX(x) * Scale(0.1, 0.2, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0.2, y, -0.2 - z) * RotateX(x) * Scale(0.05, 0.2, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Than
void Ghe()
{
    Ghe_view = Translate(0.95, -0.47, -0.25) * Translate(xghe, 0, zghe) * Scale(0.4, 0.4, 0.4) * RotateY(90);
    MakeColor(0.2, 0.8, 0.5, 1.0);

    //4 chan
    mat4 m = Translate(0.2, 0, 0.2) * Scale(0.05, 0.5, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(-0.2, 0, 0.2) * Scale(0.05, 0.5, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0.2, 0, -0.2) * Scale(0.05, 0.5, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(-0.2, 0, -0.2) * Scale(0.05, 0.5, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    //Mat ghe
    m = Translate(0, 0.25, 0) * Scale(0.45, 0.08, 0.45);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0, 0.3, -0.2) * Scale(0.45, 0.1, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    LungGhe(0, 0.35, 0.0);
    LungGhe(-3, 0.55, 0.005);
    LungGhe(-5, 0.75, 0.015);

    m = Translate(0, 0.85, -0.225) * RotateX(-8) * Scale(0.45, 0.1, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Ghe_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//======================================================================
//Cửa chính

//Khung cua
void Khung()
{
    MakeColor(1, 0.8, 0.0, 1);
    mat4 m = Translate(0.0, 0.675, 0.0) * Scale(0.6, 0.05, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0.0, -0.675, 0.0) * Scale(0.6, 0.05, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(-0.275, 0.0, 0.0) * Scale(0.05, 1.4, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0.275, 0.0, 0.0) * Scale(0.05, 1.4, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Cua
void Cua()
{
    Cua_view = Translate(-1.5, -0.08, 0.75) * RotateY(-90) * Scale(0.6, 0.7, 0.85);
    mat4 CanhCua_view = Translate(0.25, 0.0, 0.0) * RotateY(cua);

    MakeColor(0.7, 0.8, 0.2, 1);
    mat4 m = Translate(0.25, 0.0, 0.0) * Scale(0.5, 1.3, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * CanhCua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    //Num cua
    MakeColor(0.5, 0, 0.5, 1);
    m = Translate(0.4, 0.0, 0.0) * Scale(0.05, 0.05, 0.1);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Cua_view * CanhCua_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    Khung();
}

//Song cua so
void SongCua(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.02, 0.5, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Phong chung
void Phong()
{
    MakeColor(0.8, 0.8, 0.8, 1);

    mat4 m = Translate(-1.5, 0.0, -0.2) * Scale(0.05, 1.2, 1.55);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(-1.5, 0.0, 0.97) * Scale(0.05, 1.2, 0.07);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(-1.5, 0.5, 0.75) * Scale(0.05, 0.2, 0.4);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(1.5, 0.0, -0.65) * Scale(0.05, 1.2, 0.65);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(1.5, 0.0, 0.55) * Scale(0.05, 1.2, 0.9);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(1.5, 0.5, -0.125) * Scale(0.05, 0.2, 0.7);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(1.5, -0.35, -0.125) * Scale(0.05, 0.5, 0.7);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    SongCua(1.49, 0.15, 0.02);
    SongCua(1.49, 0.15, -0.1);
    SongCua(1.49, 0.15, -0.22);

    m = Translate(0, 0, -1) * Scale(3.05, 1.2, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);

    m = Translate(0, -0.6, 0) * Scale(3.05, 0.05, 2);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//==============================================================//
/*=======				Chu Văn Mạnh			===============*/

mat4 model_view_tu;
mat4 canh_tu_trai_view;
mat4 canh_tu_phai_view;
mat4 hop_tu_view;
GLdouble canh1 = 0.0, canh2 = 0.0, zhop = 0.0;

// Khung tu
void MatBenTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.03, 0.7, 0.25);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void MatTrenTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.65, 0.03, 0.25);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void MatSauTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.71, 0.70, 0.03);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void KeTuNgangTren(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.5, 0, 1);

    mat4 m = Translate(x, y, z) * Scale(0.63, 0.02, 0.25);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void KeTuNgangDuoi(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.5, 0, 1);

    mat4 m = Translate(x, y, z) * Scale(0.63, 0.02, 0.23);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void KeTuDoc(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.5, 0.2, 1);

    mat4 m = Translate(x, y, z) * Scale(0.02, 0.25, 0.23);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Canh Cua Tu
void CanhCuaTrai(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.8, 0.9, 1);

    mat4 m = Translate(x, y, z) * Scale(0.315, 0.252, 0.02);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * canh_tu_trai_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void CanhCuaPhai(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0.6, 0.1, 0.6, 1);

    mat4 m = Translate(x, y, z) * Scale(0.315, 0.252, 0.02);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * canh_tu_phai_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Hop tu
void MatTruocHopTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.63, 0.11, 0.02);

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * hop_tu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void MatSauHopTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.63, 0.1, 0.02);

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * hop_tu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void MatBenHopTu(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.02, 0.1, 0.21);

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * hop_tu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void MatDayHopTu(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.3, 1, 1);

    mat4 m = Translate(x, y, z) * Scale(0.59, 0.02, 0.21);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_view_tu * hop_tu_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void HopTu(GLfloat x, GLfloat y, GLfloat z)
{
    MakeColor(0, 0.8, 0, 1);

    hop_tu_view = Translate(0.0, 0.0, zhop) * Translate(x, y, z);

    MatTruocHopTu(0.0, 0.0, 0.115);
    MatBenHopTu(-0.305, 0.0, 0.0);
    MatBenHopTu(0.305, 0.0, 0.0);
    MatDayHopTu(0.0, -0.045, 0.0);
    MatSauHopTu(0.0, 0.0, -0.11);
}

GLfloat theta_Tu[] = {0, 0, 0, 0, 0, 0, 0, 0};
void Tu()
{
    MakeColor(0, 0.5, 0.5, 1);

    model_view_tu = Translate(0.5, -0.22, -0.78) * Scale(0.3, 0.5, 0.6) * RotateY(theta_Tu[1]) * RotateX(theta_Tu[2]) * Translate(0, theta_Tu[5], 0) * Translate(theta_Tu[6], 0, 0) * Translate(0, 0, theta_Tu[7]) * Scale(2, 2, 2);

    canh_tu_trai_view = Translate(-0.32, -0.08, 0.12) * RotateY(canh1) * Translate(0.32, 0.08, -0.12);
    canh_tu_phai_view = Translate(0.32, -0.08, 0.12) * RotateY(canh2) * Translate(-0.32, 0.08, -0.12);

    // Khung tu
    MatBenTu(0.34, 0.0, 0.0);
    MatBenTu(-0.34, 0.0, 0.0);
    MatTrenTu(0.0, 0.335, 0.0);
    MatTrenTu(0.0, -0.335, 0.0);
    MatSauTu(0.0, 0.0, -0.115);

    //Khung trong tu
    KeTuNgangTren(0.0, 0.05, 0.0);
    KeTuNgangDuoi(0.0, -0.215, 0.0);
    KeTuDoc(0.0, -0.08, 0.0);

    // 2 canh cua u
    CanhCuaTrai(-0.157, -0.08, 0.115);
    CanhCuaPhai(0.157, -0.08, 0.115);

    // Hop tu
    HopTu(0.0, -0.27, 0.0);
}

//Quạt
mat4 Canhquat_view;
mat4 Quat_view;

void Quat_chandoc(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(0.0, 0.5 * y, 0) * Scale(x, y, z);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, Quat_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Quat_canh(GLint g, GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = RotateY(g) * Translate(x, y, z) * Scale(0.5, 0.01, 0.2);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, Quat_view * Canhquat_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Quat_de()
{
    mat4 m = Translate(0, 0.2, 0) * Scale(0.05, 0.02, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, Quat_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Quat_chan()
{
    chandoc(0.03, 0.2, 0.03);
    de();
}

void Quat_canhcc()
{
    canh(90, -0.5 * 0.5, 0.0, 0.0);
    canh(-30, -0.5 * 0.5, 0.0, 0.0);
    canh(-150, -0.5 * 0.5, 0.0, 0.0);
}

GLfloat theta_Quat[] = {0, 0, 0, 0, 0, 0, 0, 0};
void Quat()
{
    Quat_view = Translate(0, 0.45, 0) * Scale(0.5, 0.5, 0.5) * RotateY(theta_Quat[1]) * RotateX(theta_Quat[2]) * Translate(0, theta_Quat[5], 0) * Translate(theta_Quat[6], 0, 0) * Translate(0, 0, theta_Quat[7]) * RotateY(180) * Scale(2, 2, 2);

    Canhquat_view = Translate(theta_Quat[6], theta_Quat[5], theta_Quat[7]) * RotateY(theta_Quat[0]);

    Quat_chan();
    Quat_canhcc();
}

//==============================================================//
/*=======				Lê Trung Hiếu    		===============*/

GLfloat dich = 0.0, Alpha = 0.0, Alphatest = 0.0, trai = 0.0, phai = 0.0;

mat4 Giuong_view;

void chan_giuong(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.05, 0.3, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Giuong_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void mat_giuong(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(1.2, 0.2, 0.8);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Giuong_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void lung_giuong(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.05, 0.6, 0.8);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Giuong_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void goi(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.15, 0.05, 0.2);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * Giuong_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void giuong()
{
    MakeColor(0.2, 0.5, 0.7, 1);
    Giuong_view = Translate(-0.7, -0.3, -0.4) * Scale(1.2, 1, 1.5);
    chan_giuong(0.5 * (1.2 - 0.05), -0.5 * (0.3), 0.5 * (0.8 - 0.05));
    chan_giuong(-0.5 * (1.2 - 0.05), -0.5 * (0.3), 0.5 * (0.8 - 0.05));
    chan_giuong(-0.5 * (1.2 - 0.05), -0.5 * (0.3), -0.5 * (0.8 - 0.05));
    chan_giuong(0.5 * (1.2 - 0.05), -0.5 * (0.3), -0.5 * (0.8 - 0.05));
    mat_giuong(0, -0.5 * 0.2, 0);
    lung_giuong(-0.5 * (+1.2 - 0.05), 0.5 * (0.6) - 0.2, 0);
    goi(-0.5 * 0.15 - 0.35, 0.5 * 0.05, 0.5 * 0.2 + 0.05);
    goi(-0.5 * 0.15 - 0.35, 0.5 * 0.05, -0.5 * 0.2 - 0.05);
}

mat4 CuaSo_view, CanhTrai_view, CanhPhai_view;

void CanhTrai(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.35, 1.3, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * CuaSo_view * CanhTrai_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void CanhPhai(GLfloat x, GLfloat y, GLfloat z)
{
    mat4 m = Translate(x, y, z) * Scale(0.35, 1.3, 0.05);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * CuaSo_view * CanhPhai_view * m);
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void CuaSo()
{
    MakeColor(0.5, 0.3, 0.3, 1);

    CuaSo_view = Translate(1.51, 0.15, -0.11) * Scale(0.5, 0.4, 0.6) * RotateY(-90);

    CanhTrai_view = Translate(-0.35, 0.0, 0.0) * RotateY(trai);
    CanhPhai_view = Translate(0.35, 0.0, 0.0) * RotateY(phai);
    CanhTrai(0.175, 0.0, 0.0);
    CanhPhai(-0.175, 0.0, 0.0);
}

//==============================================================//
/*=======				Phần chung			===============*/

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 viewer_pos(0, 0, 2);
    point4 eye(px * sin(py) * cos(pz), px * sin(py) * sin(pz), px * cos(py), 1.0);
    vec4 at(0, 0, 1, 1);
    vec4 up(0, 1, 0, 1);

    view = LookAt(eye, at, up);
    glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);

    projection = Frustum(-0.5, 0.5, -0.5, 0.5, 1, 50);
    glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
    model = RotateX(xphong) * RotateY(yphong) * RotateZ(zphong);

    Ban();
    Den();
    Ghe();
    Cua();
    Phong();
    Tu();
    Quat();
    giuong();
    CuaSo();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{
    // keyboard handler
    switch (key)
    {

        /*=======	Thọ_key	========*/

    case 'C':
        if (cua < 180)
            cua += 5;
        glutPostRedisplay();
        break;
    case 'c':
        if (cua > 50)
            cua -= 5;
        glutPostRedisplay();
        break;

    case 'x':
        xphong += 5;
        if (xphong > 360)
            xphong -= 360;
        glutPostRedisplay();
        break;
    case 'X':
        // một số lệnh
        xphong -= 5;
        if (xphong > 360)
            xphong -= 360;
        glutPostRedisplay();
        break;

    case 'y':
        // một số lệnh
        yphong += 5;
        if (yphong > 360)
            yphong -= 360;
        glutPostRedisplay();
        break;
    case 'Y':
        // một số lệnh
        yphong -= 5;
        if (yphong > 360)
            yphong -= 360;
        glutPostRedisplay();
        break;

    case 'z':
        // một số lệnh
        zphong += 5;
        if (zphong > 360)
            zphong -= 360;
        glutPostRedisplay();
        break;
    case 'Z':
        // một số lệnh
        zphong -= 5;
        if (zphong > 360)
            zphong = 0;
        glutPostRedisplay();
        break;

    case 'o': //Mở cửa tủ
        if (cuatu < 160)
            cuatu += 5;
        glutPostRedisplay();
        break;
    case 'i': //Đóng cửa tủ
        if (cuatu > 0)
            cuatu -= 5;
        glutPostRedisplay();
        break;
    case 'r': //kéo hộp bàn ra
        if (zhopban < 0.25)
            zhopban += 0.015;
        glutPostRedisplay();
        break;
    case 't': //kéo hộp bàn vào
        if (zhopban >= 0.015)
            zhopban -= 0.015;
        glutPostRedisplay();
        break;
    case 'w': //Kéo sang trái nếu ghế ở ngoài bàn
        if (zghe < 0.35 && xghe <= 0.03)
            zghe += 0.01;
        glutPostRedisplay();
        break;
    case 'e': //Kéo sang phải nếu ghế ở ngoài bàn
        if (zghe > -0.1 && xghe <= 0.03)
            zghe -= 0.01;
        glutPostRedisplay();
        break;
    case 'q': //Kéo ghế vào
        if (xghe < 0.18 && zghe <= 0.1)
            xghe += 0.01;
        glutPostRedisplay();
        break;
    case 'Q': //Kéo ghế ra
        if (xghe > -0.05 && zghe <= 0.1)
            xghe -= 0.01;
        glutPostRedisplay();
        break;
    case 'd': //Bẻ đèn cong xuống
        if (d2 > -10)
            d2 -= 0.5;
        glutPostRedisplay();
        break;
    case 'D': //Bẻ đèn cong lên
        if (d2 < 0)
            d2 += 0.5;
        glutPostRedisplay();
        break;
    case 'f': //Xoay đèn
        d1 += 5;
        glutPostRedisplay();
        break;
    case 'F': //Xoay đèn
        d1 -= 5;
        glutPostRedisplay();
        break;

    case '0':
        xphong = 4.0;
        yphong = 0.0;
        zphong = 0.0;
        glutPostRedisplay();
        break;

        /*=======	Mạnh_key	========*/

        // Chuyển động của tủ
    case '1':
        // Tu đi lên
        theta_Tu[5] += 0.05;
        theta_Tu[0] -= 15;
        theta_Tu[4] -= 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;
    case '2':
        // Tu đi  xuống
        theta_Tu[5] -= 0.05;
        theta_Tu[0] -= 15;
        theta_Tu[4] -= 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;
    case '3':
        // Tu đi về bên trái
        if (theta_Tu[6] > -0.75)
            theta_Tu[6] -= 0.05;
        theta_Tu[0] += 15;
        theta_Tu[4] += 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;
    case '4':
        // Tu đi về bên phải
        if (theta_Tu[6] < 0.75)
            theta_Tu[6] += 0.05;
        theta_Tu[0] += 15;
        theta_Tu[4] += 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;
    case '5':
        // Tu đi về trước
        theta_Tu[7] += 0.05;
        theta_Tu[0] += 15;
        theta_Tu[4] += 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;
    case '6':
        // Tu đi về sau
        if (theta_Tu[7] > 0.05)
            theta_Tu[7] -= 0.05;
        theta_Tu[0] += 15;
        theta_Tu[4] += 15;
        if (theta_Tu[0] > 360)
            theta_Tu[0] -= 360;
        if (theta_Tu[4] > 360)
            theta_Tu[4] -= 360;
        glutPostRedisplay();
        break;

    case 'v':
        if (canh1 > -100)
            canh1 -= 5;
        glutPostRedisplay();
        break;
    case 'V':
        if (canh1 < 0)
            canh1 += 5;
        glutPostRedisplay();
        break;
    case 'b':
        if (canh2 < 100)
            canh2 += 5;
        glutPostRedisplay();
        break;
    case 'B':
        if (canh2 > 0)
            canh2 -= 5;
        glutPostRedisplay();
        break;

    case 'n': //kéo ra
        if (zhop < 0.21)
            zhop += 0.015;
        glutPostRedisplay();
        break;
    case 'N': //kéo vào
        if (zhop >= 0.015)
            zhop -= 0.015;
        glutPostRedisplay();
        break;

        // Chuyển động của quạt
    case 'm':
        //Cánh quạt quay
        theta_Quat[0] += 15;
        theta_Quat[4] += 15;
        if (theta_Quat[0] > 360)
            theta_Quat[0] -= 360;
        if (theta_Quat[4] > 360)
            theta_Quat[4] -= 360;
        glutPostRedisplay();
        break;
    case 'M':
        //Cánh quạt quay
        theta_Quat[0] -= 15;
        theta_Quat[4] -= 15;
        if (theta_Quat[0] < -360)
            theta_Quat[0] = 360;
        if (theta_Quat[4] < -360)
            theta_Quat[4] = 360;
        glutPostRedisplay();
        break;

        /*=======	Dũng_key	========*/

    case 'h':
        if (trai < 160)
            trai += 5;
        glutPostRedisplay();
        break;
    case 'H':
        if (trai > 0)
            trai -= 5;
        glutPostRedisplay();
        break;
    case 'J':
        if (phai < 0)
            phai += 5;
        glutPostRedisplay();
        break;
    case 'j':
        if (phai > -160)
            phai -= 5;
        glutPostRedisplay();
        break;
        /*=======	Key chung	========*/

    case ',':
        //if (px < 2)
        px += 0.1;

        glutPostRedisplay();
        break;
    case '<':
        //if (px > -2)
        px -= 0.1;
        glutPostRedisplay();
        break;
    case '.':
        //if (py < 2)
        py += 0.1;
        glutPostRedisplay();
        break;
    case '>':
        //if (py > 0)
        py -= 0.1;
        glutPostRedisplay();
        break;
    case '/':
        //if (pz < 4)
        pz += 0.1;
        glutPostRedisplay();
        break;
    case '?':
        //if (pz > 0)
        pz -= 0.1;
        glutPostRedisplay();
        break;

    case ' ': // reset values to their defaults
        px = 4.0;
        py = 0.0;
        pz = 0.0;
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 0);
    glutCreateWindow("Nhóm 13: Phòng cá nhân");

    glewInit();

    generateGeometry();
    initGPUBuffers();
    shaderSetup();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
