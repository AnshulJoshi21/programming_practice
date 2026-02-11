import xml.etree.ElementTree as ET
import pyray as p


def spritesheet_xml_parser(xml_path: str) -> dict[str, p.Rectangle]:
    tree = ET.parse(xml_path)
    root = tree.getroot()

    sprite_dict: dict[str, p.Rectangle] = {}

    for sprite in root.findall("SubTexture"):
        name: str = sprite.attrib["name"]
        x: int = int(sprite.attrib["x"])
        y: int = int(sprite.attrib["y"])
        width: int = int(sprite.attrib["width"])
        height: int = int(sprite.attrib["height"])

        sprite_dict[name] = p.Rectangle(x, y, width, height)

    return sprite_dict
