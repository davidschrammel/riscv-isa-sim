//fprintf(stderr, "\033[0;32mSpike: uret. pc old = 0x%llx. new pc = uepc = 0x%llx\033[0m\n", p->get_state()->pc, p->get_state()->uepc);

set_pc_and_serialize(p->get_state()->uepc);
reg_t s = STATE.mstatus;
//reg_t prev_prv = get_field(s, MSTATUS_SPP);
s = set_field(s, MSTATUS_UIE, get_field(s, MSTATUS_UPIE));
s = set_field(s, MSTATUS_UPIE, 1);
//p->set_privilege(prev_prv);
p->set_privilege(PRV_U);
p->get_state()->mpkey.set_mode(0);
p->set_csr(CSR_MSTATUS, s);
//TODO
//"Execution of URET will place the uepc, ucause, and utval back into initial state."
//"An NS field can be added to mstatus and sstatus following the format of the FS and XS fields to reduce context-switch overhead when the values are not live"
