project('tpu', 'c',subproject_dir: 'lib',default_options: [
	'param:have_fopen=true', 
	'param:vmem_fram=false', 
	'param:list_dynamic=true',
])

sources = files([
	'src/main.c',
	'src/hooks.c',
    'src/serial.c',
])


deps = []
deps += dependency('csp', fallback: ['csp', 'csp_dep'])
deps += dependency('param', fallback: ['param', 'param_dep'])
deps += dependency('csp_ftp', fallback: ['csp_ftp', 'csp_ftp_dep'])

tpu_serv = executable('tpu_serv', sources,
	dependencies : deps,
	install : true,
)

