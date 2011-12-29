#!/bin/sh

src_dir="debian/libqt4-dbg/usr/lib/debug/.build-id"
dest_dir="debian/qt4-bin-dbg/usr/lib/debug/.build-id"

for binary in `find debian/tmp/usr/bin -type f -print`; do
  build_id=`eu-readelf --notes ${binary} | grep Build.ID: | awk '{print $3}'`
  build_id_dir=`echo ${build_id} | cut -c1-2`
  build_id_file=`echo ${build_id} | cut -c3-`
  base_file=${src_dir}/${build_id_dir}/${build_id_file}.debug
  if [ -f ${base_file} ] ; then
    mkdir -p ${dest_dir}/${build_id_dir}
    mv ${base_file} ${dest_dir}/${build_id_dir}
    rmdir --ignore-fail-on-non-empty ${src_dir}/${build_id_dir}
  fi
done
