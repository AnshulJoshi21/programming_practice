#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/xml_parser.h"

Textures
xml_parser(const char* xml_path)
{
    xmlDocPtr doc = NULL;
    xmlDocPtr root = NULL;
    Textures textures;
    int count = 0;

    doc = xmlReadFile(xml_path, NULL, 0);
    if (doc == NULL)
    {
        fprintf(stderr, "Failed to parse xml\n");
        exit(EXIT_FAILURE);
    }

    root = xmlDocGetRootElement(doc);
    if (root == NULL || xmlStrcmp(root->name, ( const xmlChar* ) "TextureAtlas") != 0)
    {
        fprintf(stderr, "Missing 'TextureAtlas' in xml file\n");
        xmlFreeDoc(doc);
        exit(EXIT_FAILURE);
    }

        
}