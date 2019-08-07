// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ui.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ui_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ui_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ui_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ui_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ui_2eproto;
namespace SummaryCardBusiEntry {
class ui;
class uiDefaultTypeInternal;
extern uiDefaultTypeInternal _ui_default_instance_;
}  // namespace SummaryCardBusiEntry
PROTOBUF_NAMESPACE_OPEN
template<> ::SummaryCardBusiEntry::ui* Arena::CreateMaybeMessage<::SummaryCardBusiEntry::ui>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace SummaryCardBusiEntry {

// ===================================================================

class ui :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SummaryCardBusiEntry.ui) */ {
 public:
  ui();
  virtual ~ui();

  ui(const ui& from);
  ui(ui&& from) noexcept
    : ui() {
    *this = ::std::move(from);
  }

  inline ui& operator=(const ui& from) {
    CopyFrom(from);
    return *this;
  }
  inline ui& operator=(ui&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ui& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ui* internal_default_instance() {
    return reinterpret_cast<const ui*>(
               &_ui_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ui& a, ui& b) {
    a.Swap(&b);
  }
  inline void Swap(ui* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ui* New() const final {
    return CreateMaybeMessage<ui>(nullptr);
  }

  ui* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ui>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ui& from);
  void MergeFrom(const ui& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ui* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SummaryCardBusiEntry.ui";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ui_2eproto);
    return ::descriptor_table_ui_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUrlFieldNumber = 1,
    kTitleFieldNumber = 2,
    kContentFieldNumber = 3,
    kJumpUrlFieldNumber = 4,
  };
  // optional string url = 1;
  bool has_url() const;
  void clear_url();
  const std::string& url() const;
  void set_url(const std::string& value);
  void set_url(std::string&& value);
  void set_url(const char* value);
  void set_url(const char* value, size_t size);
  std::string* mutable_url();
  std::string* release_url();
  void set_allocated_url(std::string* url);

  // optional string title = 2;
  bool has_title() const;
  void clear_title();
  const std::string& title() const;
  void set_title(const std::string& value);
  void set_title(std::string&& value);
  void set_title(const char* value);
  void set_title(const char* value, size_t size);
  std::string* mutable_title();
  std::string* release_title();
  void set_allocated_title(std::string* title);

  // optional string content = 3;
  bool has_content() const;
  void clear_content();
  const std::string& content() const;
  void set_content(const std::string& value);
  void set_content(std::string&& value);
  void set_content(const char* value);
  void set_content(const char* value, size_t size);
  std::string* mutable_content();
  std::string* release_content();
  void set_allocated_content(std::string* content);

  // optional string jump_url = 4;
  bool has_jump_url() const;
  void clear_jump_url();
  const std::string& jump_url() const;
  void set_jump_url(const std::string& value);
  void set_jump_url(std::string&& value);
  void set_jump_url(const char* value);
  void set_jump_url(const char* value, size_t size);
  std::string* mutable_jump_url();
  std::string* release_jump_url();
  void set_allocated_jump_url(std::string* jump_url);

  // @@protoc_insertion_point(class_scope:SummaryCardBusiEntry.ui)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr url_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr title_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr content_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr jump_url_;
  friend struct ::TableStruct_ui_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ui

// optional string url = 1;
inline bool ui::has_url() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ui::clear_url() {
  url_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& ui::url() const {
  // @@protoc_insertion_point(field_get:SummaryCardBusiEntry.ui.url)
  return url_.GetNoArena();
}
inline void ui::set_url(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SummaryCardBusiEntry.ui.url)
}
inline void ui::set_url(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  url_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SummaryCardBusiEntry.ui.url)
}
inline void ui::set_url(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SummaryCardBusiEntry.ui.url)
}
inline void ui::set_url(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SummaryCardBusiEntry.ui.url)
}
inline std::string* ui::mutable_url() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:SummaryCardBusiEntry.ui.url)
  return url_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ui::release_url() {
  // @@protoc_insertion_point(field_release:SummaryCardBusiEntry.ui.url)
  if (!has_url()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return url_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ui::set_allocated_url(std::string* url) {
  if (url != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  url_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), url);
  // @@protoc_insertion_point(field_set_allocated:SummaryCardBusiEntry.ui.url)
}

// optional string title = 2;
inline bool ui::has_title() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ui::clear_title() {
  title_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& ui::title() const {
  // @@protoc_insertion_point(field_get:SummaryCardBusiEntry.ui.title)
  return title_.GetNoArena();
}
inline void ui::set_title(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  title_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SummaryCardBusiEntry.ui.title)
}
inline void ui::set_title(std::string&& value) {
  _has_bits_[0] |= 0x00000002u;
  title_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SummaryCardBusiEntry.ui.title)
}
inline void ui::set_title(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000002u;
  title_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SummaryCardBusiEntry.ui.title)
}
inline void ui::set_title(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000002u;
  title_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SummaryCardBusiEntry.ui.title)
}
inline std::string* ui::mutable_title() {
  _has_bits_[0] |= 0x00000002u;
  // @@protoc_insertion_point(field_mutable:SummaryCardBusiEntry.ui.title)
  return title_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ui::release_title() {
  // @@protoc_insertion_point(field_release:SummaryCardBusiEntry.ui.title)
  if (!has_title()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return title_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ui::set_allocated_title(std::string* title) {
  if (title != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  title_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), title);
  // @@protoc_insertion_point(field_set_allocated:SummaryCardBusiEntry.ui.title)
}

// optional string content = 3;
inline bool ui::has_content() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ui::clear_content() {
  content_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000004u;
}
inline const std::string& ui::content() const {
  // @@protoc_insertion_point(field_get:SummaryCardBusiEntry.ui.content)
  return content_.GetNoArena();
}
inline void ui::set_content(const std::string& value) {
  _has_bits_[0] |= 0x00000004u;
  content_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SummaryCardBusiEntry.ui.content)
}
inline void ui::set_content(std::string&& value) {
  _has_bits_[0] |= 0x00000004u;
  content_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SummaryCardBusiEntry.ui.content)
}
inline void ui::set_content(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000004u;
  content_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SummaryCardBusiEntry.ui.content)
}
inline void ui::set_content(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000004u;
  content_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SummaryCardBusiEntry.ui.content)
}
inline std::string* ui::mutable_content() {
  _has_bits_[0] |= 0x00000004u;
  // @@protoc_insertion_point(field_mutable:SummaryCardBusiEntry.ui.content)
  return content_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ui::release_content() {
  // @@protoc_insertion_point(field_release:SummaryCardBusiEntry.ui.content)
  if (!has_content()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000004u;
  return content_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ui::set_allocated_content(std::string* content) {
  if (content != nullptr) {
    _has_bits_[0] |= 0x00000004u;
  } else {
    _has_bits_[0] &= ~0x00000004u;
  }
  content_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:SummaryCardBusiEntry.ui.content)
}

// optional string jump_url = 4;
inline bool ui::has_jump_url() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ui::clear_jump_url() {
  jump_url_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000008u;
}
inline const std::string& ui::jump_url() const {
  // @@protoc_insertion_point(field_get:SummaryCardBusiEntry.ui.jump_url)
  return jump_url_.GetNoArena();
}
inline void ui::set_jump_url(const std::string& value) {
  _has_bits_[0] |= 0x00000008u;
  jump_url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SummaryCardBusiEntry.ui.jump_url)
}
inline void ui::set_jump_url(std::string&& value) {
  _has_bits_[0] |= 0x00000008u;
  jump_url_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SummaryCardBusiEntry.ui.jump_url)
}
inline void ui::set_jump_url(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000008u;
  jump_url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SummaryCardBusiEntry.ui.jump_url)
}
inline void ui::set_jump_url(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000008u;
  jump_url_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SummaryCardBusiEntry.ui.jump_url)
}
inline std::string* ui::mutable_jump_url() {
  _has_bits_[0] |= 0x00000008u;
  // @@protoc_insertion_point(field_mutable:SummaryCardBusiEntry.ui.jump_url)
  return jump_url_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ui::release_jump_url() {
  // @@protoc_insertion_point(field_release:SummaryCardBusiEntry.ui.jump_url)
  if (!has_jump_url()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000008u;
  return jump_url_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ui::set_allocated_jump_url(std::string* jump_url) {
  if (jump_url != nullptr) {
    _has_bits_[0] |= 0x00000008u;
  } else {
    _has_bits_[0] &= ~0x00000008u;
  }
  jump_url_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), jump_url);
  // @@protoc_insertion_point(field_set_allocated:SummaryCardBusiEntry.ui.jump_url)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace SummaryCardBusiEntry

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ui_2eproto
