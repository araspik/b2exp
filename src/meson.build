asm_support = {
    'darwin': ['x86_64']
}

if asm_support.get(host_os,[]).contains(host_cpu)
    source = 'asm/@0@.@1@.S'.format(host_os, host_cpu)
else
    source = 'b2exp.c'
endif

lib = library('b2exp',
    'lut.c', source,
    include_directories: all_includes,
)
