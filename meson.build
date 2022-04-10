project(
  'zigen', 'c',
  version: '0.0.1',
  license: 'MIT',
  meson_version: '>= 0.52.1',
  default_options:  ['warning_level=3', 'werror=true', 'optimization=2']
)

src_inc = include_directories('src')

pkgconfig = import('pkgconfig')

subdir('protocol')
subdir('src')
subdir('tests')
