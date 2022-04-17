/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: commandmessage.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "commandmessage.pb-c.h"
void   aaproto__command_message__led_commands__init
                     (Aaproto__CommandMessage__LedCommands         *message)
{
  static const Aaproto__CommandMessage__LedCommands init_value = AAPROTO__COMMAND_MESSAGE__LED_COMMANDS__INIT;
  *message = init_value;
}
void   aaproto__command_message__init
                     (Aaproto__CommandMessage         *message)
{
  static const Aaproto__CommandMessage init_value = AAPROTO__COMMAND_MESSAGE__INIT;
  *message = init_value;
}
size_t aaproto__command_message__get_packed_size
                     (const Aaproto__CommandMessage *message)
{
  assert(message->base.descriptor == &aaproto__command_message__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t aaproto__command_message__pack
                     (const Aaproto__CommandMessage *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &aaproto__command_message__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t aaproto__command_message__pack_to_buffer
                     (const Aaproto__CommandMessage *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &aaproto__command_message__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Aaproto__CommandMessage *
       aaproto__command_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Aaproto__CommandMessage *)
     protobuf_c_message_unpack (&aaproto__command_message__descriptor,
                                allocator, len, data);
}
void   aaproto__command_message__free_unpacked
                     (Aaproto__CommandMessage *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &aaproto__command_message__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor aaproto__command_message__led_commands__field_descriptors[3] =
{
  {
    "Pin",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(Aaproto__CommandMessage__LedCommands, pin),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Location",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Aaproto__CommandMessage__LedCommands, location),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "LedCmd",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Aaproto__CommandMessage__LedCommands, ledcmd),
    &aaproto__command_message__led_command__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned aaproto__command_message__led_commands__field_indices_by_name[] = {
  2,   /* field[2] = LedCmd */
  1,   /* field[1] = Location */
  0,   /* field[0] = Pin */
};
static const ProtobufCIntRange aaproto__command_message__led_commands__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor aaproto__command_message__led_commands__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "aaproto.CommandMessage.LedCommands",
  "LedCommands",
  "Aaproto__CommandMessage__LedCommands",
  "aaproto",
  sizeof(Aaproto__CommandMessage__LedCommands),
  3,
  aaproto__command_message__led_commands__field_descriptors,
  aaproto__command_message__led_commands__field_indices_by_name,
  1,  aaproto__command_message__led_commands__number_ranges,
  (ProtobufCMessageInit) aaproto__command_message__led_commands__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue aaproto__command_message__device_type__enum_values_by_number[2] =
{
  { "CONTROLLER", "AAPROTO__COMMAND_MESSAGE__DEVICE_TYPE__CONTROLLER", 0 },
  { "LED", "AAPROTO__COMMAND_MESSAGE__DEVICE_TYPE__LED", 1 },
};
static const ProtobufCIntRange aaproto__command_message__device_type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex aaproto__command_message__device_type__enum_values_by_name[2] =
{
  { "CONTROLLER", 0 },
  { "LED", 1 },
};
const ProtobufCEnumDescriptor aaproto__command_message__device_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "aaproto.CommandMessage.DeviceType",
  "DeviceType",
  "Aaproto__CommandMessage__DeviceType",
  "aaproto",
  2,
  aaproto__command_message__device_type__enum_values_by_number,
  2,
  aaproto__command_message__device_type__enum_values_by_name,
  1,
  aaproto__command_message__device_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue aaproto__command_message__led_command__enum_values_by_number[4] =
{
  { "CONFIG", "AAPROTO__COMMAND_MESSAGE__LED_COMMAND__CONFIG", 0 },
  { "SWITCH_ON", "AAPROTO__COMMAND_MESSAGE__LED_COMMAND__SWITCH_ON", 1 },
  { "SWITCH_OFF", "AAPROTO__COMMAND_MESSAGE__LED_COMMAND__SWITCH_OFF", 2 },
  { "TOGGLE", "AAPROTO__COMMAND_MESSAGE__LED_COMMAND__TOGGLE", 3 },
};
static const ProtobufCIntRange aaproto__command_message__led_command__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex aaproto__command_message__led_command__enum_values_by_name[4] =
{
  { "CONFIG", 0 },
  { "SWITCH_OFF", 2 },
  { "SWITCH_ON", 1 },
  { "TOGGLE", 3 },
};
const ProtobufCEnumDescriptor aaproto__command_message__led_command__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "aaproto.CommandMessage.LedCommand",
  "LedCommand",
  "Aaproto__CommandMessage__LedCommand",
  "aaproto",
  4,
  aaproto__command_message__led_command__enum_values_by_number,
  4,
  aaproto__command_message__led_command__enum_values_by_name,
  1,
  aaproto__command_message__led_command__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue aaproto__command_message__led_status__enum_values_by_number[4] =
{
  { "CONFIGURED", "AAPROTO__COMMAND_MESSAGE__LED_STATUS__CONFIGURED", 0 },
  { "ON", "AAPROTO__COMMAND_MESSAGE__LED_STATUS__ON", 1 },
  { "OFF", "AAPROTO__COMMAND_MESSAGE__LED_STATUS__OFF", 2 },
  { "UNKNOWN", "AAPROTO__COMMAND_MESSAGE__LED_STATUS__UNKNOWN", 3 },
};
static const ProtobufCIntRange aaproto__command_message__led_status__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex aaproto__command_message__led_status__enum_values_by_name[4] =
{
  { "CONFIGURED", 0 },
  { "OFF", 2 },
  { "ON", 1 },
  { "UNKNOWN", 3 },
};
const ProtobufCEnumDescriptor aaproto__command_message__led_status__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "aaproto.CommandMessage.LedStatus",
  "LedStatus",
  "Aaproto__CommandMessage__LedStatus",
  "aaproto",
  4,
  aaproto__command_message__led_status__enum_values_by_number,
  4,
  aaproto__command_message__led_status__enum_values_by_name,
  1,
  aaproto__command_message__led_status__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor aaproto__command_message__field_descriptors[3] =
{
  {
    "Device",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Aaproto__CommandMessage, device),
    &aaproto__command_message__device_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "LedCmds",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Aaproto__CommandMessage, n_ledcmds),
    offsetof(Aaproto__CommandMessage, ledcmds),
    &aaproto__command_message__led_commands__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "TransactionTimestamp",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Aaproto__CommandMessage, transactiontimestamp),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned aaproto__command_message__field_indices_by_name[] = {
  0,   /* field[0] = Device */
  1,   /* field[1] = LedCmds */
  2,   /* field[2] = TransactionTimestamp */
};
static const ProtobufCIntRange aaproto__command_message__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor aaproto__command_message__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "aaproto.CommandMessage",
  "CommandMessage",
  "Aaproto__CommandMessage",
  "aaproto",
  sizeof(Aaproto__CommandMessage),
  3,
  aaproto__command_message__field_descriptors,
  aaproto__command_message__field_indices_by_name,
  1,  aaproto__command_message__number_ranges,
  (ProtobufCMessageInit) aaproto__command_message__init,
  NULL,NULL,NULL    /* reserved[123] */
};