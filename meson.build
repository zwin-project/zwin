project(
  'zwin', 'c',
  version: '0.0.2',
  license: 'MIT',
  meson_version: '>= 0.58.0',
  default_options:  ['warning_level=3', 'werror=true', 'optimization=2']
)

cc = meson.get_compiler('c')

global_args = []
global_args_maybe = [
  '-fvisibility=hidden',
  '-Wstrict-prototypes',
]

foreach arg : global_args_maybe
  if cc.has_argument(arg)
    global_args += arg
  endif
endforeach
add_project_arguments(global_args, language: 'c')

wayland_server_dep = dependency('wayland-server')

pkgconfig = import('pkgconfig')

subdir('protocol')
subdir('tests')
