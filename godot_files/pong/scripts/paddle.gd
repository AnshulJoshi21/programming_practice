extends CharacterBody2D

var screen_size: Vector2

var width: float
var height: float
var speed: float
var color_: Color
var is_player: bool

func _ready() -> void:
	screen_size = get_viewport_rect().size
	width = 10.0
	height = 100.0
	global_position = Vector2(0, screen_size.y/2.0 - height/2.0)
	speed = 300.0
	color_ = Color.BLACK
	
func _draw() -> void:
	draw_rect(Rect2(Vector2.ZERO, Vector2(width, height)), color_)

func move_player(delta:float) -> void:
	screen_size = get_viewport_rect().size
	if Input.is_action_pressed("paddle_up") and position.y - height/2.0 > 0:
		position.y -= speed * delta
	if Input.is_action_pressed("paddle_down") and position.y + height/2.0 < screen_size.y:
		position.y += speed * delta 
	
func move_ai(delta: float) -> void:
	screen_size = get_viewport_rect().size
	if $ball.position.y < position.y - height/2.0 and position.y - height/2.0 > 0:
		position.y -= speed * delta
	if $ball.position.y > position.y + height/2.0 and position.y + height/2.0 < screen_size.y:
		position.y += speed * delta

func _physics_process(delta: float) -> void:
	if is_player:
		move_player(delta)
	else:
		move_ai(delta)
	
