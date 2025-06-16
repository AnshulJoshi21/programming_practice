#ifndef XML_PARSER_H
#define XML_PARSER_H

#define MAX_SUBTEXTURES 50

typedef struct SubTexture
{
    const char* name;
    const int x;
    const int y;
    const int width;
    const int height;

} SubTexture;

typedef struct Textures
{
    SubTexture arr[MAX_SUBTEXTURES];

} Textures;

Textures
xml_parser(const char* xml_path);

#endif // XML_PARSER_H