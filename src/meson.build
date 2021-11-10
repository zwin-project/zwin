zigen_version = meson.project_version().split('.')
zigen_version_h = configuration_data()
zigen_version_h.set('ZIGEN_VERSION', meson.project_version())
zigen_version_h.set('ZIGEN_VERSION_MAJOR', zigen_version[0].to_int())
zigen_version_h.set('ZIGEN_VERSION_MINOR', zigen_version[1].to_int())
zigen_version_h.set('ZIGEN_VERSION_MICRO', zigen_version[2].to_int())
configure_file(
  input: 'zigen-version.h.in',
  output: 'zigen-version.h',
  configuration: zigen_version_h,
  install: get_option('libraries'),
  install_dir: join_paths(get_option('prefix'), get_option('includedir')),
)

if get_option('libraries')
  install_headers([
    'zigen-util.h'
  ])
endif
