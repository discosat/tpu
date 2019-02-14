project('tpu', 'c',subproject_dir: 'lib',default_options: [
	'csp:packet_padding_bytes=42', 
	'csp:buffer_count=1000',
	'csp:buffer_size=2048',
	'csp:conn_max=20',
	'csp:conn_rxqueue_len=1000',
	'csp:qfifo_len=1000',
	'csp:rdp_max_window=1000',
	'csp:port_max_bind=16',
	'param:have_fopen=true', 
	'param:vmem_fram=false', 
	'param:list_dynamic=true',
])

sources = files([
	'src/main.c',
	'src/hooks.c',
    'src/serial.c',
    'src/csp_hooks.c',
    'src/bootcnt.c',
    'src/executor/executor.c',
    'src/slotname.c',
    'src/vmem_config.c',
])


csp_dep = dependency('csp', fallback: ['csp', 'csp_dep'])
param_dep = dependency('param', fallback: ['param', 'param_dep'])
ftp_dep = dependency('csp_ftp', fallback: ['csp_ftp', 'csp_ftp_dep'])

deps = [csp_dep,param_dep,ftp_dep]

c_args = '-DHOSTNAME="@0@"'.format(get_option('hostname'))

tpu_serv = executable('tpu_serv', sources,
	dependencies : deps,
	install : true,
    c_args : c_args,
)

boot_increment_src = files([
    'src/boot_increment.c',
    'src/bootcnt.c',
    'src/vmem_config.c',
])

boot_increment_deps = [param_dep]
boot_increment = executable('boot_increment', boot_increment_src,
	dependencies : boot_increment_deps,
	install : true,
)
