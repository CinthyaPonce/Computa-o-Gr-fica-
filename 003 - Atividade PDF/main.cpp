
#include "main.h"

#define IMAGE_WIDTH 512 // Define a largura que vamos utilizar em pixels
#define IMAGE_HEIGHT 512 // Define a altura que vamos utilizar em pixels

float vertices[] = {-0.25f, -0.5f, -0.1f, 0.75f, 0.0f, 0.0f,
                     0.25f,  0.5f, -0.1f, 0.75f, 0.0f, 0.0f,
                     0.75f, -0.5f, -0.1f, 0.75f, 0.0f, 0.0f,
                    -0.75f, -0.5f, -0.4f, 0.0f, 0.0f, 0.75f,
                    -0.25f,  0.5f, -0.4f, 0.0f, 0.0f, 0.75f,
                     0.25f, -0.5f, -0.4f, 0.0f, 0.0f, 0.75f};

char* frag_shader_source = NULL;
char* vertex_shader_source = NULL;
unsigned int shader_program;
unsigned int vbo;
unsigned int vao;

void LoadShader(char* file_name, char** shader_source) {
    long length;
    FILE* f = fopen(file_name, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        (*shader_source) = (char*)malloc(length + 1);
        if ((*shader_source)) {
            fread((*shader_source), 1, length, f);
            (*shader_source)[length] = '\0';
        }

        fclose(f);
    } else {
        printf("Could not load the shader file %s\nExiting...", file_name);
        exit(EXIT_FAILURE);
    }
}

void Display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);


    glUseProgram(shader_program);

    // FOI UTILIZADO ESSE TRECHO PARA CONSEGUIRMOS EVIDENCIAR A RESOLUCAO DA SEGUNDA QUESTAO

   /* float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             -0.4f, 0.0f, 1.0f, 0.0f,
                             0.9f, 0.0f, 1.0f, 1.0f}; */


    float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             -0.3f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.5f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat = glm::make_mat4(model_array);


    // FOI UTILIZADO ESSE TRECHO PARA CONSEGUIRMOS EVIDENCIAR A RESOLUCAO DA QUARTA QUESTAO + TRECHO DA TERCEIRA QUESTAO,
    /*
    float view_array[16] = {0.9f, 0.0f, 0.0f, 1.0f,
                            0.5f, -1.0f, 0.0f, -1.0f,
                            0.9f, 0.0f, 1.3f, 0.0f,
                            0.0f, 0.2f, -0.3f, 1.0f}; */

    float view_array[16] = {1.0f, -0.2f, 0.0f, 0.5f,
                            0.5f, -1.0f, 0.0f, .0f,
                            0.5f, 0.2f, 1.0f, -1.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};

    glm::mat4 view_mat = glm::make_mat4(view_array);


    // FOI UTILIZADO ESSE TRECHO PARA CONSEGUIRMOS EVIDENCIAR A RESOLUCAO DA PRIMEIRA QUESTAO
    float proj_array[16] = {-0.8f, 0.0f, 0.5f, 0.0f,
                            0.0f, 1.0f, -0.2f, 0.0f,
                            0.8f, -0.2f, 0.5f, 0.0f,
                            0.0f, 0.0f, 0.5f, 1.0f};


    // FOI UTILIZADO ESSE TRECHO PARA CONSEGUIRMOS EVIDENCIAR A RESOLUCAO DA TERCEIRA QUESTAO
   /* float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, -0.2f, 0.0f,
                            0.0f, 0.0f, 1.0f, -2.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};
                            */
    glm::mat4 proj_mat = glm::make_mat4(proj_array);

    float flip_z_array[16] = {1.0f, 0.0f,  0.0f, 0.0f,
                              0.0f, 1.0f,  0.0f, 0.0f,
                              0.0f, 0.0f, -1.0f, 0.0f,
                              0.0f, 0.0f,  0.0f, 1.0f};
    glm::mat4 flip_z_mat = glm::make_mat4(flip_z_array);

    glm::mat4 model_view_proj_mat = flip_z_mat * proj_mat * view_mat * model_mat;

    unsigned int transformLoc;
    GL_CHECK(transformLoc = glGetUniformLocation(shader_program, "transform"));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat));

    glBindVertexArray(vao);

    // Desenha comecando pelo zero
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glFlush();            //
    glutSwapBuffers();    //
    glutPostRedisplay();  //
}

void ExitProg(void) {
    if (vertex_shader_source) {
        free(vertex_shader_source);
        vertex_shader_source = NULL;
    }

    if (frag_shader_source) {
        free(frag_shader_source);
        frag_shader_source = NULL;
    }

    printf("Exiting...\n");
}

int main(int argc, char** argv) {

    // Comeca inicializado o GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Atividade 3");

    GLenum err = glewInit();
    if (GLEW_OK != err) {
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      return EXIT_FAILURE;
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    LoadShader("vertex_shader.glsl", &vertex_shader_source);

    printf("%s\n", vertex_shader_source);

    unsigned int vertex_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);r
    glCompileShader(vertex_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
    }

    LoadShader("fragment_shader.glsl", &frag_shader_source);

    printf("%s\n", frag_shader_source);

    unsigned int fragment_shader;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
    }

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Cor

    GL_CHECK(glEnable(GL_DEPTH_TEST)); // Habilita profundidade [obtive erro no inicio]

    atexit(ExitProg);
    glutDisplayFunc(Display);


    glutMainLoop();

    return EXIT_SUCCESS;
}
