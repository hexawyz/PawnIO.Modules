//  PawnIO Modules - Modules for various hardware to be used with PawnIO.
//  Copyright (C) 2023  namazso <admin@namazso.eu>
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#define SIGN_EXTEND(%1,%2) (((%1) << (cellbits - (%2))) >> (cellbits - (%2)))
#define SIGN_EXTEND8(%1) (SIGN_EXTEND(%1, 8))
#define SIGN_EXTEND16(%1) (SIGN_EXTEND(%1, 16))
#define SIGN_EXTEND32(%1) (SIGN_EXTEND(%1, 32))

#define CHAR4_CONST(%1,%2,%3,%4) ((%1) | ((%2) << 8)  | ((%3) << 16) | ((%4) << 24))

stock _min(a, b) {
    return a < b ? a : b;
}

stock _max(a, b) {
    return a > b ? a : b;
}

#define PAGE_SIZE (0x1000)

#define BIT(%1) (1 << (%1))

stock unpack_bytes_le(src[], dst[], size, src_offs = 0, dst_offs = 0) {
    for (new i = 0; i < size; i++) {
        new src_idx = src_offs + i;
        new src_cell = src[src_idx / 8];
        new byte = (src_cell >> ((src_idx % 8) * 8)) & 0xff;
        dst[dst_offs + i] = byte;
    }
}

stock pack_bytes_le(src[], dst[], size, src_offs = 0, dst_offs = 0) {
    for (new i = 0; i < size; i++) {
        new byte = src[src_offs + i] & 0xff;
        new dst_idx = dst_offs + i;
        dst[dst_idx / 8] &= ~(0xff << ((dst_idx % 8) * 8));
        dst[dst_idx / 8] |= byte << ((dst_idx % 8) * 8);
    }
}
