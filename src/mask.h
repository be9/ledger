/*
 * Copyright (c) 2003-2009, John Wiegley.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of New Artisans LLC nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup util
 */

/**
 * @file   mask.h
 * @author John Wiegley
 *
 * @ingroup util
 *
 * @brief Regular expression masking.
 */
#ifndef _MASK_H
#define _MASK_H

#include "utils.h"

namespace ledger {

/**
 * @brief Brief
 *
 * Long.
 */
class mask_t
{
public:
  boost::regex expr;

  explicit mask_t(const string& pattern);

  mask_t() : expr() {
    TRACE_CTOR(mask_t, "");
  }
  mask_t(const mask_t& m) : expr(m.expr) {
    TRACE_CTOR(mask_t, "copy");
  }
  ~mask_t() throw() {
    TRACE_DTOR(mask_t);
  }

  mask_t& operator=(const string& other);

  bool operator==(const mask_t& other) const {
    return expr == other.expr;
  }

  bool match(const string& str) const {
    DEBUG("mask.match",
	  "Matching: \"" << str << "\" =~ /" << expr.str() << "/ = "
	  << (boost::regex_search(str, expr) ? "true" : "false"));
    return boost::regex_search(str, expr);
  }

  bool empty() const {
    return expr.empty();
  }

  bool valid() const {
    if (expr.status() != 0) {
      DEBUG("ledger.validate", "mask_t: expr.status() != 0");
      return false;
    }
    return true;
  }
};

inline std::ostream& operator<<(std::ostream& out, const mask_t& mask) {
  out << mask.expr.str();
  return out;
}

} // namespace ledger

#endif // _MASK_H
