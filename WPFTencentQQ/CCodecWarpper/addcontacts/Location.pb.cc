// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Location.proto

#include "Location.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace AccountSearchPb {
class LocationDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Location> _instance;
} _Location_default_instance_;
}  // namespace AccountSearchPb
static void InitDefaultsscc_info_Location_Location_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::AccountSearchPb::_Location_default_instance_;
    new (ptr) ::AccountSearchPb::Location();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::AccountSearchPb::Location::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Location_Location_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_Location_Location_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Location_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Location_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Location_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Location_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::AccountSearchPb::Location, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::AccountSearchPb::Location, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::AccountSearchPb::Location, double_latitude_),
  PROTOBUF_FIELD_OFFSET(::AccountSearchPb::Location, double_longitude_),
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::AccountSearchPb::Location)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::AccountSearchPb::_Location_default_instance_),
};

const char descriptor_table_protodef_Location_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Location.proto\022\017AccountSearchPb\"C\n\010Loc"
  "ation\022\032\n\017double_latitude\030\001 \001(\001:\0010\022\033\n\020dou"
  "ble_longitude\030\002 \001(\001:\0010"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Location_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_Location_2eproto_sccs[1] = {
  &scc_info_Location_Location_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Location_2eproto_once;
static bool descriptor_table_Location_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Location_2eproto = {
  &descriptor_table_Location_2eproto_initialized, descriptor_table_protodef_Location_2eproto, "Location.proto", 102,
  &descriptor_table_Location_2eproto_once, descriptor_table_Location_2eproto_sccs, descriptor_table_Location_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_Location_2eproto::offsets,
  file_level_metadata_Location_2eproto, 1, file_level_enum_descriptors_Location_2eproto, file_level_service_descriptors_Location_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Location_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_Location_2eproto), true);
namespace AccountSearchPb {

// ===================================================================

void Location::InitAsDefaultInstance() {
}
class Location::_Internal {
 public:
  using HasBits = decltype(std::declval<Location>()._has_bits_);
  static void set_has_double_latitude(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_double_longitude(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

Location::Location()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AccountSearchPb.Location)
}
Location::Location(const Location& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&double_latitude_, &from.double_latitude_,
    static_cast<size_t>(reinterpret_cast<char*>(&double_longitude_) -
    reinterpret_cast<char*>(&double_latitude_)) + sizeof(double_longitude_));
  // @@protoc_insertion_point(copy_constructor:AccountSearchPb.Location)
}

void Location::SharedCtor() {
  ::memset(&double_latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&double_longitude_) -
      reinterpret_cast<char*>(&double_latitude_)) + sizeof(double_longitude_));
}

Location::~Location() {
  // @@protoc_insertion_point(destructor:AccountSearchPb.Location)
  SharedDtor();
}

void Location::SharedDtor() {
}

void Location::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Location& Location::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Location_Location_2eproto.base);
  return *internal_default_instance();
}


void Location::Clear() {
// @@protoc_insertion_point(message_clear_start:AccountSearchPb.Location)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&double_latitude_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&double_longitude_) -
        reinterpret_cast<char*>(&double_latitude_)) + sizeof(double_longitude_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Location::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional double double_latitude = 1 [default = 0];
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 9)) {
          _Internal::set_has_double_latitude(&has_bits);
          double_latitude_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // optional double double_longitude = 2 [default = 0];
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 17)) {
          _Internal::set_has_double_longitude(&has_bits);
          double_longitude_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Location::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:AccountSearchPb.Location)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double double_latitude = 1 [default = 0];
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (9 & 0xFF)) {
          _Internal::set_has_double_latitude(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &double_latitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional double double_longitude = 2 [default = 0];
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (17 & 0xFF)) {
          _Internal::set_has_double_longitude(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &double_longitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AccountSearchPb.Location)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AccountSearchPb.Location)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Location::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AccountSearchPb.Location)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional double double_latitude = 1 [default = 0];
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(1, this->double_latitude(), output);
  }

  // optional double double_longitude = 2 [default = 0];
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(2, this->double_longitude(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AccountSearchPb.Location)
}

::PROTOBUF_NAMESPACE_ID::uint8* Location::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AccountSearchPb.Location)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional double double_latitude = 1 [default = 0];
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(1, this->double_latitude(), target);
  }

  // optional double double_longitude = 2 [default = 0];
  if (cached_has_bits & 0x00000002u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(2, this->double_longitude(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AccountSearchPb.Location)
  return target;
}

size_t Location::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AccountSearchPb.Location)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional double double_latitude = 1 [default = 0];
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 + 8;
    }

    // optional double double_longitude = 2 [default = 0];
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + 8;
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Location::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:AccountSearchPb.Location)
  GOOGLE_DCHECK_NE(&from, this);
  const Location* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Location>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:AccountSearchPb.Location)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:AccountSearchPb.Location)
    MergeFrom(*source);
  }
}

void Location::MergeFrom(const Location& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:AccountSearchPb.Location)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      double_latitude_ = from.double_latitude_;
    }
    if (cached_has_bits & 0x00000002u) {
      double_longitude_ = from.double_longitude_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Location::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:AccountSearchPb.Location)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Location::CopyFrom(const Location& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AccountSearchPb.Location)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Location::IsInitialized() const {
  return true;
}

void Location::InternalSwap(Location* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(double_latitude_, other->double_latitude_);
  swap(double_longitude_, other->double_longitude_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Location::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace AccountSearchPb
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::AccountSearchPb::Location* Arena::CreateMaybeMessage< ::AccountSearchPb::Location >(Arena* arena) {
  return Arena::CreateInternal< ::AccountSearchPb::Location >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
