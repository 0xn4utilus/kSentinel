export const tracingFields = [
    { placeholder: 'sys_enter_execve', label: 'sys_enter' },
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' },
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_exit' },
    { placeholder: 'puts', label: 'ufunction_entry' },
    { placeholder: 'puts', label: 'ufunction_exit' },
];

export const blockingFields = [
    { placeholder: 'sys_enter_execve', label: 'sys_enter*' },
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' },
    { placeholder: 'prepare_kernel_cred', label: 'kfunction_exit' },
    { placeholder: 'puts', label: 'ufunction_entry' },
    { placeholder: 'puts', label: 'ufunction_exit' },
]