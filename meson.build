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
])


deps = []
deps += dependency('csp', fallback: ['csp', 'csp_dep'])
deps += dependency('param', fallback: ['param', 'param_dep'])
deps += dependency('csp_ftp', fallback: ['csp_ftp', 'csp_ftp_dep'])

tpu_serv = executable('tpu_serv', sources,
	dependencies : deps,
	install : true,
)

