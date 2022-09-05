//
// Created by Jacopo Gasparetto on 04/09/22.
//

#ifndef A2DHS_VISIBILITYPOLYGON_H
#define A2DHS_VISIBILITYPOLYGON_H

#include <Godot.hpp>
#include <Gradient.hpp>
#include <GradientTexture2D.hpp>
#include <Polygon2D.hpp>
#include <algorithm>
#include <memory>
#include <vector>

#include "CoreMath.h"
#include "Map.h"
#include "Player.h"

struct Edge {
  godot::Vector2 a;
  godot::Vector2 b;
  Edge(const godot::Vector2 &_a, const godot::Vector2 &_b) : a(_a), b(_b) {}
};

class VisibilityPolygon : public godot::Polygon2D {
  GODOT_CLASS(VisibilityPolygon, godot::Polygon2D);

  const Player *m_player;
  godot::Vector2 screen_size;
  std::vector<const Polygon2D *> m_walls{};
  std::vector<godot::Vector2> m_vertices{};
  std::vector<Edge> m_edges{};
  std::vector<godot::Vector2> m_intersections;

  godot::Ref<godot::Gradient> m_gradient;
  godot::Ref<godot::GradientTexture2D> m_texture;

public:
  void _init(){};
  void _ready();
  void _draw();
  void _process();
  godot::Vector2 hitTest(godot::Vector2 const &ray);
  void add_wall(const godot::Polygon2D *wall);
  void set_walls(std::vector<const Polygon2D *> &walls);
  void set_player(const Player *player);
  static void _register_methods();
};

#endif // A2DHS_VISIBILITYPOLYGON_H
