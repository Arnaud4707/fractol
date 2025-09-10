#!/usr/bin/env sh

# Copyright (C) 2008-2017 Erik de Castro Lopo <erikd@mega-nerd.com>
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in
#       the documentation and/or other materials provided with the
#       distribution.
#     * Neither the author nor the names of any contributors may be used
#       to endorse or promote products derived from this software without
#       specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


HOST_TRIPLET=x86_64-pc-linux-gnu
PACKAGE_VERSION=1.2.2
LIB_VERSION=$(echo $PACKAGE_VERSION | sed "s/[a-z].*//")
ABS_TOP_SRCDIR=/home/amugisha/git_perso/fractol/libsndfile-1.2.2
PYTHON=/usr/bin/python

sfversion=$(./tests/sfversion | grep libsndfile | sed "s/-exp$//")

if test "$sfversion" != libsndfile-$PACKAGE_VERSION ; then
	echo "Error : sfversion ($sfversion) and PACKAGE_VERSION ($PACKAGE_VERSION) don't match."
	exit 1
	fi

# Force exit on errors.
set -e

# Check the header file.
/usr/bin/env sh tests/pedantic-header-test.sh

# Need this for when we're running from files collected into the
# libsndfile-testsuite-1.2.2 tarball.
echo "Running unit tests from src/ directory of source code tree."
./src/test_main

echo
echo "Running end-to-end tests from tests/ directory."

./tests/error_test
./tests/pcm_test
./tests/ulaw_test
./tests/alaw_test
./tests/dwvw_test
./tests/command_test ver
./tests/command_test norm
./tests/command_test format
./tests/command_test peak
./tests/command_test trunc
./tests/command_test inst
./tests/command_test cue
./tests/command_test current_sf_info
./tests/command_test bext
./tests/command_test bextch
./tests/command_test chanmap
./tests/command_test cart
./tests/floating_point_test
./tests/checksum_test
./tests/scale_clip_test
./tests/headerless_test
./tests/rdwr_test
./tests/locale_test
./tests/win32_ordinal_test
./tests/external_libs_test
./tests/format_check_test
./tests/channel_test

# The w64 G++ compiler requires an extra runtime DLL which we don't have,
# so skip this test.
case "$HOST_TRIPLET" in
	x86_64-w64-mingw32)
		;;
	i686-w64-mingw32)
		;;
	*)
		./tests/cpp_test
		;;
	esac

echo "----------------------------------------------------------------------"
echo "  $sfversion passed common tests."
echo "----------------------------------------------------------------------"

# aiff-tests
./tests/write_read_test aiff
./tests/lossy_comp_test aiff_ulaw
./tests/lossy_comp_test aiff_alaw
./tests/lossy_comp_test aiff_gsm610
echo "----------------------------------------------------------------------"
echo "  lossy_comp_test aiff_ima"
echo "----------------------------------------------------------------------"

./tests/peak_chunk_test aiff
./tests/header_test aiff
./tests/misc_test aiff
./tests/string_test aiff
./tests/multi_file_test aiff
./tests/aiff_rw_test
./tests/chunk_test aiff
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on AIFF files."
echo "----------------------------------------------------------------------"

# au-tests
./tests/write_read_test au
./tests/lossy_comp_test au_ulaw
./tests/lossy_comp_test au_alaw
./tests/lossy_comp_test au_g721
./tests/lossy_comp_test au_g723
./tests/header_test au
./tests/misc_test au
./tests/multi_file_test au
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on AU files."
echo "----------------------------------------------------------------------"

# caf-tests
./tests/write_read_test caf
./tests/lossy_comp_test caf_ulaw
./tests/lossy_comp_test caf_alaw
./tests/header_test caf
./tests/peak_chunk_test caf
./tests/misc_test caf
./tests/chunk_test caf
./tests/string_test caf
./tests/long_read_write_test alac
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on CAF files."
echo "----------------------------------------------------------------------"

# wav-tests
./tests/write_read_test wav
./tests/lossy_comp_test wav_pcm
./tests/lossy_comp_test wav_ima
./tests/lossy_comp_test wav_msadpcm
./tests/lossy_comp_test wav_ulaw
./tests/lossy_comp_test wav_alaw
./tests/lossy_comp_test wav_gsm610
./tests/lossy_comp_test wav_g721
./tests/peak_chunk_test wav
./tests/header_test wav
./tests/misc_test wav
./tests/string_test wav
./tests/multi_file_test wav
./tests/chunk_test wav
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on WAV files."
echo "----------------------------------------------------------------------"

# w64-tests
./tests/write_read_test w64
./tests/lossy_comp_test w64_ima
./tests/lossy_comp_test w64_msadpcm
./tests/lossy_comp_test w64_ulaw
./tests/lossy_comp_test w64_alaw
./tests/lossy_comp_test w64_gsm610
./tests/header_test w64
./tests/misc_test w64
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on W64 files."
echo "----------------------------------------------------------------------"

# rf64-tests
./tests/write_read_test rf64
./tests/header_test rf64
./tests/misc_test rf64
./tests/string_test rf64
./tests/peak_chunk_test rf64
./tests/chunk_test rf64
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on RF64 files."
echo "----------------------------------------------------------------------"

# raw-tests
./tests/write_read_test raw
./tests/lossy_comp_test raw_ulaw
./tests/lossy_comp_test raw_alaw
./tests/lossy_comp_test raw_gsm610
./tests/lossy_comp_test vox_adpcm
./tests/raw_test
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on RAW (header-less) files."
echo "----------------------------------------------------------------------"

# paf-tests
./tests/write_read_test paf
./tests/header_test paf
./tests/misc_test paf
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on PAF files."
echo "----------------------------------------------------------------------"

# svx-tests
./tests/write_read_test svx
./tests/header_test svx
./tests/misc_test svx
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on SVX files."
echo "----------------------------------------------------------------------"

# nist-tests
./tests/write_read_test nist
./tests/lossy_comp_test nist_ulaw
./tests/lossy_comp_test nist_alaw
./tests/header_test nist
./tests/misc_test nist
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on NIST files."
echo "----------------------------------------------------------------------"

# ircam-tests
./tests/write_read_test ircam
./tests/lossy_comp_test ircam_ulaw
./tests/lossy_comp_test ircam_alaw
./tests/header_test ircam
./tests/misc_test ircam
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on IRCAM files."
echo "----------------------------------------------------------------------"

# voc-tests
./tests/write_read_test voc
./tests/lossy_comp_test voc_ulaw
./tests/lossy_comp_test voc_alaw
./tests/header_test voc
./tests/misc_test voc
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on VOC files."
echo "----------------------------------------------------------------------"

# mat4-tests
./tests/write_read_test mat4
./tests/header_test mat4
./tests/misc_test mat4
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on MAT4 files."
echo "----------------------------------------------------------------------"

# mat5-tests
./tests/write_read_test mat5
./tests/header_test mat5
./tests/misc_test mat5
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on MAT5 files."
echo "----------------------------------------------------------------------"

# pvf-tests
./tests/write_read_test pvf
./tests/header_test pvf
./tests/misc_test pvf
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on PVF files."
echo "----------------------------------------------------------------------"

# xi-tests
./tests/lossy_comp_test xi_dpcm
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on XI files."
echo "----------------------------------------------------------------------"

# htk-tests
./tests/write_read_test htk
./tests/header_test htk
./tests/misc_test htk
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on HTK files."
echo "----------------------------------------------------------------------"

# avr-tests
./tests/write_read_test avr
./tests/header_test avr
./tests/misc_test avr
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on AVR files."
echo "----------------------------------------------------------------------"

# sds-tests
./tests/write_read_test sds
./tests/header_test sds
./tests/misc_test sds
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on SDS files."
echo "----------------------------------------------------------------------"

# sd2-tests
./tests/write_read_test sd2
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on SD2 files."
echo "----------------------------------------------------------------------"

# wve-tests
./tests/lossy_comp_test wve
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on WVE files."
echo "----------------------------------------------------------------------"

# mpc2k-tests
./tests/write_read_test mpc2k
./tests/header_test mpc2k
./tests/misc_test mpc2k
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on MPC 2000 files."
echo "----------------------------------------------------------------------"

# flac-tests
./tests/write_read_test flac
./tests/compression_size_test flac
./tests/string_test flac
./tests/header_test flac
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on FLAC files."
echo "----------------------------------------------------------------------"

# vorbis-tests
./tests/ogg_test
./tests/compression_size_test vorbis
./tests/lossy_comp_test ogg_vorbis
./tests/string_test ogg
./tests/misc_test ogg
echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on OGG/VORBIS files."
echo "----------------------------------------------------------------------"

# opus-tests
./tests/ogg_opus_test
./tests/compression_size_test opus
./tests/lossy_comp_test ogg_opus
./tests/string_test opus

echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on OPUS files."
echo "----------------------------------------------------------------------"

# mpeg-tests
./tests/mpeg_test
./tests/compression_size_test mpeg
./tests/string_test mpeg

echo "----------------------------------------------------------------------"
echo "  $sfversion passed tests on MPEG files."
echo "----------------------------------------------------------------------"

# io-tests
./tests/stdio_test
./tests/pipe_test
./tests/virtual_io_test
echo "----------------------------------------------------------------------"
echo "  $sfversion passed stdio/pipe/vio tests."
echo "----------------------------------------------------------------------"

"${PYTHON}" "${ABS_TOP_SRCDIR}/src/binheader_writef_check.py" "${ABS_TOP_SRCDIR}/src"/*.c
echo "----------------------------------------------------------------------"
echo "  $sfversion passed binary header tests."
echo "----------------------------------------------------------------------"

"${PYTHON}" "${ABS_TOP_SRCDIR}/programs/test-sndfile-metadata-set.py" "${HOST_TRIPLET}"
echo "----------------------------------------------------------------------"
echo "  $sfversion passed sndfile metadata tests."
echo "----------------------------------------------------------------------"
