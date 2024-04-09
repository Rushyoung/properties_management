```mermaid
graph LR
start --> login
login --> verify{username&password} 
verify -->|admin| admin
verify --> |residents| residents
verify --> |workers| workers
verify --> |fail| login

admin --> admin_main
admin_main --> work_select1{work_select}
admin_main --> password_maintain1
admin_main --> password_change1
work_select1 --> |to_residents| residents_manage
work_select1 --> |to_workers| worker_manage
work_select1 --> |to_fee| fee
work_select1 --> |to_data| data
data --> backup
data --> restore
residents_manage --> repair_request
residents_manage --> add_resident
residents_manage --> remove_resident
residents_manage --> inquire_resident
fee --> select
fee --> sort
fee --> to_singal
select --> List_of_unpaid
select --> List_of_paid_overtime
sort --> sort_by_name
sort --> sort_by_lastest_paytime
to_singal --> bil
to_singal --> Paid_overtime
to_singal --> unpaid
worker_manage --> work_assignments
worker_manage --> add_worker
worker_manage --> remove_worker
work_assignments --> repair
work_assignments --> clean
work_assignments --> remind_payment

workers --> worker_main
worker_main --> inquire_work
worker_main --> sort2
worker_main --> count_work
worker_main --> complete_work
worker_main --> password_change2
worker_main --> password_maintain2
inquire_work --> region
inquire_work --> content

residents -->  residents_main
residents_main --> fee1
residents_main --> problem_report
residents_main --> inquire
residents_main --> password_change3
residents_main --> password_maintain3
fee1 --> unpaid_bills
fee1 --> paid_overtime
fee1 --> pay
fee1 --> history1
history1 --> sort3
history1 --> select2
history1 --> count1
problem_report --> add_problem
problem_report --> view_problem
problem_report --> history2
history2 --> sort4
history2 --> select3
history2 --> count2
inquire --> workers_list
inquire --> fee_standard

bill_include_id_time_username_money
```