#include "../systems.hpp"
#include "../utils.hpp"
#include "drop.hpp"

static const float DROP_RADIUS = 20.0f;

Drop::Drop(const DropType drop_type, const Vector2& start_pos)
    : state({.active = true}), position({.x = start_pos.x, .y = start_pos.y}),
      circle({.radius = DROP_RADIUS}), color({.tint = ORANGE}),
      text({.text = "", .font_size = 20.0f, .spacing = 2.0f, .tint = WHITE}) {
    //
    amount = 0;
    type   = drop_type;

    switch (type) {
        case DropType::XP:
            text.text = "XP";
            amount    = 20;
            break;

        case DropType::HP:
            text.text = "HP";
            amount    = 10;
            break;

        case DropType::NONE:
            state.active = false;
            break;
    }
}

void Drop::draw(void) const {
    Systems::draw_circle(position, circle, color);
    Utils::center_and_draw_text(Utils::OriginType::CENTER,
                                {position.x, position.y, circle.radius * 2, circle.radius * 2},
                                text);
}
