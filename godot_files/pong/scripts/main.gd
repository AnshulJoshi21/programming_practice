extends Node2D

var screen_size: Vector2

var ball_scene: PackedScene
var ball: CharacterBody2D

var paddle_scene: PackedScene
var player: CharacterBody2D
var ai: CharacterBody2D

func _ready() -> void:
	screen_size = get_viewport_rect().size
	
	ball_scene = preload("res://scenes/ball.tscn")
	ball = ball_scene.instantiate()
	
	paddle_scene = preload("res://scenes/paddle.tscn")
	player = paddle_scene.instantiate()
	player.global_position.x = 10.0
	player.is_player = true
	add_child(player)
	
	ai = paddle_scene.instantiate()
	ai.global_position.x = screen_size.x - player.width - 10.0
	ai.is_player = false
	add_child(ai)


func _process(delta: float) -> void:
	pass
