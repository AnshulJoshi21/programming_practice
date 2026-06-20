from typing import Literal

from flask import Flask, Response, jsonify, request

app = Flask(__name__)

notes: list[dict[str, int | str | bool]] = [
    {"id": 1, "title": "A", "completed": False},
    {"id": 2, "title": "B", "completed": False},
    {"id": 3, "title": "C", "completed": False},
]


@app.route("/")
def home() -> Response:
    return jsonify({"message": "Home"})


@app.route("/notes", methods=["GET"])
def get_notes() -> Response:
    return jsonify(notes)


@app.route("/notes/<int:note_id>")
def get_note(note_id: int) -> Response | tuple[Response, Literal[404]]:
    for note in notes:
        if note["id"] == note_id:
            return jsonify(note)

    return jsonify({"error": "Note not found"}), 404


@app.route("/notes", methods=["POST"])
def create_note() -> Response | tuple[Response, Literal[404]]:
    data: dict[str, str] = request.get_json()

    if not data or "title" not in data:
        return jsonify({"error": "title is required"}), 404

    note: dict[str, int | str | bool] = {
        "id": len(notes) + 1,
        "title": data["title"],
        "completed": False,
    }
    notes.append(note)

    return jsonify(note)


@app.route("/notes/<int:note_id>", methods=["PUT"])
def update_note(note_id: int) -> Response | tuple[Response, Literal[404]]:
    data: dict[str, str] = request.get_json()

    for note in notes:
        if note["id"] == note_id:
            note["title"] = data["title"]
            return jsonify(note)

    return jsonify({"error": "Note not found"}), 404


@app.route("/notes/<int:note_id>/completed", methods=["PUT"])
def update_note_complete(note_id: int) -> Response | tuple[Response, Literal[404]]:
    data: dict[str, bool] = request.get_json()

    for note in notes:
        if note["id"] == note_id:
            note["completed"] = data["completed"]
            return jsonify(note)

    return jsonify({"error": "Note not found"}), 404


@app.route("/notes/<int:note_id>", methods=["DELETE"])
def delete_note(note_id: int) -> Response | tuple[Response, Literal[404]]:
    for note in notes:
        if note["id"] == note_id:
            notes.remove(note)
            return jsonify({"message": "Deleted"})

    return jsonify({"error": "Note not found"}), 404


if __name__ == "__main__":
    app.run(debug=True)
