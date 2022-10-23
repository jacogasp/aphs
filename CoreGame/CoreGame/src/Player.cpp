//
// Created by Jacopo Gasparetto on 30/08/22.
//
#include "Player.h"
#include <algorithm>
#include <iostream>

#include "DialogueTrigger.h"

void Player::_ready() {
  m_animatedSprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
  m_torch = get_node<Torch>("Torch");
  m_animatedSprite->set_animation("walk");
  godot::Godot::print("Player ready");
}

std::ostream &operator<<(std::ostream &os, const godot::Vector2 &v) { return os << "x: " << v.x << ", y: " << v.y; }

void Player::_physics_process(const real_t p_delta) {
  if (!m_userInteractionEnabled) {
    m_animatedSprite->stop();
    return;
  }
  auto input = godot::Input::get_singleton();
  godot::Vector2 velocity{0, 0};
  velocity.x = input->get_action_strength("move_right") - input->get_action_strength("move_left");
  velocity.y = input->get_action_strength("move_down") - input->get_action_strength("move_up");
  float inputMagnitude = std::clamp(velocity.length(), 0.0f, 1.0f);
  auto collision = move_and_collide(velocity * speed * inputMagnitude * p_delta);

  if (velocity.length() > 0.0f) {
    float angle = velocity.angle();
    m_animatedSprite->play();
    set_global_rotation(godot::Math::lerp_angle(get_global_rotation(), angle, rotation_weight));
  } else {
    m_animatedSprite->stop();
  }
}

godot::Vector2 Player::get_direction() const {
  godot::Vector2 v{};
  v.set_rotation(get_global_rotation());
  return v;
}

void Player::_on_Player_area_entered(godot::Area2D *area) {
  if (area->is_in_group("batteries")) {
    m_torch->full_charge();
    area->queue_free();
  } else if (area->is_in_group("dialogues")) {
    if (m_showDialogueCallback) {
      auto trigger = godot::Object::cast_to<DialogueTrigger>(area);
      m_showDialogueCallback(trigger->dialogueKey);
      area->queue_free();
    }
  }
}

void Player::_register_methods() {
  godot::register_property("speed", &Player::speed, (real_t)200.0f);
  godot::register_property("rotation_weight", &Player::rotation_weight, (real_t)0.5f);
  godot::register_method("_ready", &Player::_ready);
  godot::register_method("_physics_process", &Player::_physics_process);
  godot::register_method("_on_Player_area_entered", &Player::_on_Player_area_entered);
}