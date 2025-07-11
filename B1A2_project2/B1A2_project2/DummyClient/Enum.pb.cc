// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#include "Enum.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Protocol {
}  // namespace Protocol
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Enum_2eproto[2];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Enum_2eproto = nullptr;
const uint32_t TableStruct_Enum_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_Enum_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nEnum.proto\022\010Protocol*U\n\010DIR_TYPE\022\021\n\rDI"
  "R_TYPE_LEFT\020\000\022\022\n\016DIR_TYPE_RIGHT\020\001\022\017\n\013DIR"
  "_TYPE_UP\020\002\022\021\n\rDIR_TYPE_DOWN\020\003*\305\010\n\021OBJECT"
  "_STATE_TYPE\022\032\n\026OBJECT_STATE_TYPE_IDLE\020\000\022"
  "\032\n\026OBJECT_STATE_TYPE_MOVE\020\001\022\037\n\033OBJECT_ST"
  "ATE_TYPE_DUCK_DOWN\020\002\022$\n OBJECT_STATE_TYP"
  "E_DUCK_DOWN_MOVE\020\003\022\032\n\026OBJECT_STATE_TYPE_"
  "JUMP\020\004\022\"\n\036OBJECT_STATE_TYPE_CLOSE_ATTACK"
  "\020\005\022!\n\035OBJECT_STATE_TYPE_LONG_ATTACK\020\006\022(\n"
  "$OBJECT_STATE_TYPE_LONG_ATTACK_LENGTH\020\007\022"
  "\'\n#OBJECT_STATE_TYPE_LONG_ATTACK_WIDTH\020\010"
  "\022\034\n\030OBJECT_STATE_TYPE_THRUST\020\t\022\037\n\033OBJECT"
  "_STATE_TYPE_BACK_STEP\020\n\022 \n\034OBJECT_STATE_"
  "TYPE_SLASH_WAVE\020\013\022!\n\035OBJECT_STATE_TYPE_S"
  "KILL_READY\020\014\022#\n\037OBJECT_STATE_TYPE_SKILL_"
  "WAITING\020\r\022\037\n\033OBJECT_STATE_TYPE_SKILL_END"
  "\020\016\022\032\n\026OBJECT_STATE_TYPE_HANG\020\017\022\035\n\031OBJECT"
  "_STATE_TYPE_RELEASE\020\020\022\031\n\025OBJECT_STATE_TY"
  "PE_HIT\020\021\022\032\n\026OBJECT_STATE_TYPE_DEAD\020\022\022\033\n\027"
  "OBJECT_STATE_TYPE_CHASE\020\023\022\035\n\031OBJECT_STAT"
  "E_TYPE_ROAMING\020\024\022\032\n\026OBJECT_STATE_TYPE_DA"
  "SH\020\025\022\034\n\030OBJECT_STATE_TYPE_RETURN\020\026\022!\n\035OB"
  "JECT_STATE_TYPE_RETURN_IDLE\020\027\022%\n!OBJECT_"
  "STATE_TYPE_PROJECTILE_FALL\020\030\022&\n\"OBJECT_S"
  "TATE_TYPE_CRYSTAL_CREATION\020\031\022&\n\"OBJECT_S"
  "TATE_TYPE_MONSTER_CREATION\020\032\022\036\n\032OBJECT_S"
  "TATE_TYPE_TELEPORT\020\033\022\"\n\036OBJECT_STATE_TYP"
  "E_CUT_SEVERELY\020\034\022\030\n\024OBJECT_STATE_TYPE_ON"
  "\020\035\022\031\n\025OBJECT_STATE_TYPE_ON2\020\036\022\033\n\027OBJECT_"
  "STATE_TYPE_READY\020\037\022\031\n\025OBJECT_STATE_TYPE_"
  "OFF\020 b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_Enum_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Enum_2eproto = {
    false, false, 1213, descriptor_table_protodef_Enum_2eproto,
    "Enum.proto",
    &descriptor_table_Enum_2eproto_once, nullptr, 0, 0,
    schemas, file_default_instances, TableStruct_Enum_2eproto::offsets,
    nullptr, file_level_enum_descriptors_Enum_2eproto,
    file_level_service_descriptors_Enum_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Enum_2eproto_getter() {
  return &descriptor_table_Enum_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Enum_2eproto(&descriptor_table_Enum_2eproto);
namespace Protocol {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* DIR_TYPE_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Enum_2eproto);
  return file_level_enum_descriptors_Enum_2eproto[0];
}
bool DIR_TYPE_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* OBJECT_STATE_TYPE_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Enum_2eproto);
  return file_level_enum_descriptors_Enum_2eproto[1];
}
bool OBJECT_STATE_TYPE_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
