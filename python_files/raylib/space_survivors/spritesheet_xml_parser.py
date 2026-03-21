import xml.etree.ElementTree as ET

from pyray import Rectangle


def spritesheet_xml_parser(spritesheet_path: str) -> dict[str, Rectangle]:
    tree: ET.ElementTree[ET.Element[str]] = ET.parse(spritesheet_path)
    root: ET.Element = tree.getroot()

    sprite_dict: dict[str, Rectangle] = {}

    for sprite in root.findall("SubTexture"):
        name: str = sprite.attrib["name"]
        x: int = int(sprite.attrib["x"])
        y: int = int(sprite.attrib["y"])
        width: int = int(sprite.attrib["width"])
        height: int = int(sprite.attrib["height"])

        sprite_dict[name] = Rectangle(x, y, width, height)

    return sprite_dict
