extends Node2D

var radius: float
var speed: float
var direction: Vector2
var color_: Color

func _ready() -> void:
	var size: Vector2 = get_viewport_rect().size
	
	radius = randf_range(5, 30)
	global_position = Vector2(randf_range(radius, size.x - radius), randf_range(radius, size.y - radius))
	speed = randf_range(100, 300)
	direction = Vector2(-1 if randi_range(0, 1) == 0 else 1,-1 if randi_range(0, 1) == 0 else 1).normalized()
	color_ = Color(randf(), randf(), randf())
	
	queue_redraw()

func _draw() -> void:
	draw_circle(Vector2.ZERO, radius, color_)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	# move
	position += direction * speed * delta
	
	# bounds
	var size: Vector2 = get_viewport_rect().size
	if position.x < radius or position.x > size.x - radius:
		direction.x *= -1
		clamp(position.x, radius, size.x - radius)
	if position.y < radius or position.y > size.y - radius:
		direction.y *= -1
		clamp(position.y, radius, size.y - radius)
