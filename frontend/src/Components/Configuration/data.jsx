export const tracingFields = [
    { placeholder: 'sys_enter_execve', label: 'sys_enter' ,type:"tracing"},
    { placeholder: 'sys_exit_execve', label: 'sys_exit' ,type:"tracing"},
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' ,type:"tracing"},
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_exit' ,type:"tracing"},
    { placeholder: 'puts', label: 'ufunction_entry' ,type:"tracing"},
    { placeholder: 'puts', label: 'ufunction_exit' ,type:"tracing"},
];

export const blockingFields = [
    { placeholder: 'sys_enter_execve', label: 'sys_enter' ,type:"blocking"},
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' ,type:"blocking"},

]
