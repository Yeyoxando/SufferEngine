
#include <resource_manager.h>
#include <scoped_array.h>
#include <geometry.h>
#include <material.h>
#include <GL/glew.h>


struct Suffer::ResourceManager::ResourceData {

    struct InternalVertexBuffer {
        InternalVertexBuffer() {};
        Array<float> data_;
        u32 id_handle_;
        u32 version_;
        u32 gpu_version_;
    };

    struct InternalIndexBuffer {
        InternalIndexBuffer() {};
        Array<u16> data_;
        u32 id_handle_;
        u32 version_;
        u32 gpu_version_;
    };

    void Init();

    Array<InternalIndexBuffer> internal_index_buffers_;
    Array<InternalVertexBuffer> internal_vertex_buffers_;

    u32 number_of_vertex_buffers_;
    u32 number_of_index_buffers_;


    // Predefined geometries
    struct InternalGeometry {
        GLuint vertices_ID;
        GLuint indices_ID;
        u32 number_elements;

        void CreateGeometry(Geometry::BasicShapes shape);
    };

    // Predefined materials
    struct InternalMaterial {
        GLuint program_ID;
        GLuint vertex_shader_ID;
        GLuint fragment_shader_ID;

        void CreateMaterial(Material::BasicMaterials material);
    };

    void InitInternalGeometries();
    void InitInternalMaterials();

    InternalGeometry triangle_;
    InternalGeometry quad_;
    InternalGeometry cube_;

    InternalMaterial default_material_;
    
};

void Suffer::ResourceManager::ResourceData::InternalMaterial::CreateMaterial(Material::BasicMaterials material){
    switch (material) {
    case Material::kBasicMaterials_Default: {
        // DEFAULT SHADERS
        const GLchar* vertex_shader = R"VSHADER(
	
	#version 330
	layout(location = 0) in vec3 a_position;

	void main(){
		gl_Position = vec4(a_position, 1.0f);
	}

	)VSHADER";

        const GLchar* fragment_shader = R"FSHADER(

	#version 330

	void main(){
		gl_FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	}
	
	)FSHADER";

        // HELLO TRIANGLE STUFF -> TODO: THIS WILL BE DELETED
        GLenum error = glGetError();
        vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
        error = glGetError();
        fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
        error = glGetError();

        const GLint vertex_size = strlen(vertex_shader);
        const GLint fragment_size = strlen(fragment_shader);

        glShaderSource(vertex_shader_ID, 1, &vertex_shader, &vertex_size);
        error = glGetError();
        glShaderSource(fragment_shader_ID, 1, &fragment_shader, &fragment_size);
        error = glGetError();

        glCompileShader(vertex_shader_ID);
        error = glGetError();

        GLint status = 0;
        glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &status);
        GLint log_length = 0;
        glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* info_log = new GLchar[log_length + 1];
        glGetShaderInfoLog(vertex_shader_ID, log_length, &log_length, info_log);
        info_log[log_length] = '\0';
        delete info_log;
        if (status == GL_FALSE)
            printf("\nERROR: vertex shader not compiled");

        glCompileShader(fragment_shader_ID);
        error = glGetError();
        status = 0;
        glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &status);
        log_length = 0;
        glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
        info_log = new GLchar[log_length + 1];
        glGetShaderInfoLog(fragment_shader_ID, log_length, &log_length, info_log);
        info_log[log_length] = '\0';
        delete info_log;
        if (status == GL_FALSE)
            printf("\nERROR: fragment shader not compiled");

        // PROGRAM
        program_ID = glCreateProgram();

        glAttachShader(program_ID, vertex_shader_ID);
        glAttachShader(program_ID, fragment_shader_ID);

        glLinkProgram(program_ID);

        break;
    }
    case Material::kBasicMaterials_NONE: {
        break;
    }
    default:
        break;
    }
}

void Suffer::ResourceManager::ResourceData::InternalGeometry::CreateGeometry(Geometry::BasicShapes shape){
    switch (shape) {
    case Geometry::kBasicShapes_Triangle: {
        // BUFFERS
        float vertices[] = {
          0.0f,  0.5f, -1.0f,
          0.5f, -0.5f, -1.0f,
          -0.5f, -0.5f, -1.0f
        };

        glGenBuffers(1, &vertices_ID);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned char indices[]{ 0, 2, 1 };

        glGenBuffers(1, &indices_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        number_elements = 3;

        break;
    }
    case Geometry::kBasicShapes_Quad: {

        // BUFFERS
        float vertices[] = {
          0.5f, -0.5f, -1.0f,
          0.5f,  0.5f, -1.0f,
           -0.5f,  0.5f, -1.0f,
           -0.5f, -0.5f, -1.0f,
        };

        glGenBuffers(1, &vertices_ID);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned char indices[]{ 0, 2, 1,
                     2, 3, 0 };

        glGenBuffers(1, &indices_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        number_elements = 6;

        break;

    }
    case Geometry::kBasicShapes_Cube: {

        // BUFFERS
        float vertices[] = {
            // front
            -0.5, -0.5,  0.5,
             0.5, -0.5,  0.5,
             0.5,  0.5,  0.5,
            -0.5,  0.5,  0.5,
            // back
            -0.5, -0.5, -0.5,
             0.5, -0.5, -0.5,
             0.5,  0.5, -0.5,
            -0.5,  0.5, -0.5
        };

        glGenBuffers(1, &vertices_ID);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned char indices[]{
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };

        glGenBuffers(1, &indices_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        number_elements = 36;

        break;
    }
    case Geometry::kBasicShapes_NONE:
        break;
    default:
        break;
    }
}

void Suffer::ResourceManager::ResourceData::Init(){

    internal_index_buffers_.alloc(MAX_BUFFERS);
    internal_vertex_buffers_.alloc(MAX_BUFFERS);

    number_of_vertex_buffers_ = 0;
    number_of_index_buffers_ = 0;

}

void Suffer::ResourceManager::ResourceData::InitInternalGeometries(){
    triangle_.CreateGeometry(Geometry::kBasicShapes_Triangle);
    quad_.CreateGeometry(Geometry::kBasicShapes_Quad);
    cube_.CreateGeometry(Geometry::kBasicShapes_Cube);
}

void Suffer::ResourceManager::ResourceData::InitInternalMaterials(){
    default_material_.CreateMaterial(Material::kBasicMaterials_Default);
}

void Suffer::ResourceManager::UploadIndexData(const void* data, u32 size, u32 offset){

}

void Suffer::ResourceManager::UploadVertexData(const void* data, u32 size, u32 offset){

}

void Suffer::ResourceManager::SetPredefiniedShape(ref_ptr <Geometry> geo, Geometry::BasicShapes shape){

#ifdef ASSERT
    assert(geo.get()); // "geo was NULL"
#endif
    ResourceData::InternalGeometry predefinied_shape;

    switch (shape) {
    case Geometry::BasicShapes::kBasicShapes_Triangle:
        predefinied_shape = data_->triangle_;
        break;
    case Geometry::BasicShapes::kBasicShapes_Quad:
        predefinied_shape = data_->quad_;
        break;
    case Geometry::BasicShapes::kBasicShapes_Cube:
        predefinied_shape = data_->cube_;
        break;
    case Geometry::BasicShapes::kBasicShapes_NONE:
        break;
    default:
        break;
    }

    //geo.get()->shape_ = shape;
    //geo.get()->SetIndicesID(predefinied_shape.indices_ID);
    //geo.get()->SetVerticesID(predefinied_shape.vertices_ID);
    //geo.get()->SetNumberElements(predefinied_shape.number_elements);

}

void Suffer::ResourceManager::SetPredefiniedMaterial(ref_ptr <Material> mat, Material::BasicMaterials basic_mat){
 
#ifdef ASSERT
	  assert(mat.get()); // "mat was NULL"
 #endif
	
	ResourceData::InternalMaterial predefinied_material;
	
	switch (basic_mat) {
	case Material::BasicMaterials::kBasicMaterials_Default: {
	predefinied_material = data_->default_material_;
	break;
	}
	case Material::BasicMaterials::kBasicMaterials_NONE: {
	break;
	}
	default:
	break;
	}

	//mat.get()->material_ = basic_mat;
	//mat.get()->SetProgram(predefinied_material.program_ID);

}

Suffer::ResourceManager::ResourceManager(){
    data_ = new ResourceData();
}

Suffer::ResourceManager::~ResourceManager(){
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
}

void Suffer::ResourceManager::StartUp(){
    data_->Init();
}

void Suffer::ResourceManager::ShutDown() {

}

u32 Suffer::ResourceManager::NumberOfIndexBuffer(){
    return data_->number_of_index_buffers_;
}

u32 Suffer::ResourceManager::NumberOfVertexBuffer(){
    return data_->number_of_vertex_buffers_;
}

void Suffer::ResourceManager::VertexBuffer::Init(VertexFormat format, u32 size){
    //id_ = suffer.resource_manager_.NumberOfVertexBuffer();
}

float Suffer::ResourceManager::VertexBuffer::GetVertex(u32 index){
    return 1.0f;
}


void Suffer::ResourceManager::IndexBuffer::Init(u32 size){
    //id_ = suffer.resource_manager_.NumberOfIndexBuffer();
}

u16 Suffer::ResourceManager::IndexBuffer::GetIndex(u32 index){
    return 1;
}
