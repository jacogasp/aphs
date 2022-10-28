#include "Controller.h"
#include "DialogueTrigger.h"
#include "HUD.h"
#include "Main.h"
#include "Map.h"
#include "Mob.h"
#include "Player.h"
#include "RedEyesSpawner.h"
#include "Torch.h"
#include "VisibilityPolygon.h"
#include <Godot.hpp>

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) { Godot::gdnative_init(o); }

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
  // Crash on quit calling get_tree() https://github.com/godotengine/godot/issues/48295#issuecomment-981404421
  Godot::nativescript_terminate(godot::_RegisterState::nativescript_handle);
  Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
  Godot::nativescript_init(handle);
  register_class<Controller>();
  register_class<Player>();
  register_class<Mob>();
  register_class<Main>();
  register_class<HUD>();
  register_class<Map>();
  register_class<RedEyes>();
  register_class<RedEyesSpawner>();
  register_class<VisibilityPolygon>();
  register_class<Torch>();
  register_class<DialogueTrigger>();
}