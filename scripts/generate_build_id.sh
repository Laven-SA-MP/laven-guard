#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_FILE="$ROOT_DIR/include/generated/lg_build_signature.inc"

DATE_UTC="$(date -u +%Y-%m-%d)"
SHORT="$(date -u +%s%N | sha256sum | cut -c1-6)"
BUILD_ID="LG-${DATE_UTC}-${SHORT}"

cat > "$OUT_FILE" <<SIG
#if defined _lg_build_signature_included
    #endinput
#endif
#define _lg_build_signature_included

#define LG_BUILD_ID "${BUILD_ID}"
#define LG_COMMUNITY_LICENSE "LAVEN COMMUNITY LICENSE v1"
#define LG_HIDDEN_SIGNATURE "lvn_guard_core_sig_26x_decay"
SIG

echo "Generated $OUT_FILE"
echo "LG_BUILD_ID=${BUILD_ID}"
