import xml.etree.ElementTree as ET

from pyray import Rectangle


def xml_parser(xml_path: str) -> dict[str, Rectangle]:
    tree: ET.ElementTree[ET.Element[str]] = ET.parse(xml_path)
    root: ET.Element[str] = tree.getroot()

    sprite_dict: dict[str, Rectangle] = {}

    for sprite in root.findall("SubTexture"):
        name: str = sprite.attrib["name"]
        x: int = int(sprite.attrib["x"])
        y: int = int(sprite.attrib["y"])
        width: int = int(sprite.attrib["width"])
        height: int = int(sprite.attrib["height"])

        sprite_dict[name] = Rectangle(x, y, width, height)

    return sprite_dict
