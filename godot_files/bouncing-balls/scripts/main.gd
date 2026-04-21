extends Node2D

const MAX_BALLS = 200
@onready var BALL_SCENE: PackedScene = preload("res://scenes/ball.tscn")

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	randomize()
	for i in range(MAX_BALLS):
		var ball: Node2D = BALL_SCENE.instantiate()
		add_child(ball)
