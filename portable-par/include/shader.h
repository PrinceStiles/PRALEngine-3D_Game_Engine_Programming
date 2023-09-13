//
// Created by cedric on 7/7/23.
//

#ifndef GMTK_2023_SHADER_H
#define GMTK_2023_SHADER_H

#include <string>
#include <stdint.h>
enum shader_type {
    vertex,
    fragment,
};

class Shader
{
private:
    std::string filename;
    shader_type type;
    uint32_t shader_id;

    static std::string read_file(const std::string& filename);

public:
    explicit Shader(const char* filename, enum shader_type shader_type);
    bool compile();
    uint32_t get_shader_id() const;
    ~Shader();

};

#endif //GMTK_2023_SHADER_H
