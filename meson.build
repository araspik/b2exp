project('b2exp',
    'c',
    license: 'GPL3',
    meson_version: '>=0.50.0',
    version: '0.0.1',
)
project_desc = 'A base-2 exponential function.'
project_url = 'https://github.com/araspik/b2exp'

host_os = host_machine.system()
host_cpu = host_machine.cpu_family()

subdir('include')
subdir('src')
subdir('test')
subdir('bench')

import('pkgconfig').generate(
    description: project_desc,
    filebase: 'libb2exp',
    libraries: [lib],
    name: 'b2exp',
    subdirs: 'b2exp',
    url: project_url
)
