extends CharacterBody2D

var screen_size: Vector2
var radius: float
var speed: float
var speed_increment: float
var direction: Vector2
var color_: Color
var is_active: bool

func _ready() -> void:
	screen_size = get_viewport_rect().size
	global_position = Vector2(screen_size.x/2.0, screen_size.y/2.0)
	radius = 10.0
	speed = 300.0
	speed_increment = 10.0
	direction = Vector2(-1 if randi_range(0, 1) == 0 else 1, -1 if randi_range(0, 1) == 0 else 1)
	color_ = Color.RED
	is_active = false

func _draw() -> void:
	draw_circle(Vector2.ZERO, radius, color_)
	
func _physics_process(delta: float) -> void:
	screen_size = get_viewport_rect().size
	# activate ball
	if Input.is_action_just_pressed("activate_ball"):
		is_active = true
	
	if is_active:
		direction = direction.normalized()
		
		# move
		position += direction * speed * delta
		
		# bounds
		if position.x < radius or position.x > screen_size.x - radius:
			direction.x *= -1
			clamp(position.x, radius, screen_size.x - radius)
		if position.y < radius or position.y > screen_size.y - radius:
			direction.y *= -1
			clamp(position.y, radius, screen_size.y - radius)
		
	
