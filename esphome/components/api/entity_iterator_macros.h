#pragma once

#include "esphome/core/defines.h"
#ifdef USE_API

// Macro-based approach to eliminate duplication without runtime overhead
// This generates the entity handler methods at compile time

// For ListEntitiesIterator - calls schedule_message_ with try_send_*_info
#define LIST_ENTITIES_HANDLER(entity_type, EntityClass, ResponseType) \
  bool ListEntitiesIterator::on_##entity_type(EntityClass *entity) { \
    return this->client_->schedule_message_(entity, &APIConnection::try_send_##entity_type##_info, \
                                            ResponseType::MESSAGE_TYPE); \
  }

// For InitialStateIterator - calls send_*_state
#define INITIAL_STATE_HANDLER(entity_type, EntityClass) \
  bool InitialStateIterator::on_##entity_type(EntityClass *entity) { \
    return this->client_->send_##entity_type##_state(entity); \
  }

// Combined macro that generates both handlers
#define ENTITY_HANDLERS(entity_type, EntityClass, ResponseType) \
  LIST_ENTITIES_HANDLER(entity_type, EntityClass, ResponseType) \
  INITIAL_STATE_HANDLER(entity_type, EntityClass)

#endif  // USE_API