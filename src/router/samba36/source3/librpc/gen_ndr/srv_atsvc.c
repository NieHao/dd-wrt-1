/*
 * Unix SMB/CIFS implementation.
 * server auto-generated by pidl. DO NOT MODIFY!
 */

#include "includes.h"
#include "ntdomain.h"
#include "librpc/gen_ndr/srv_atsvc.h"

static bool api_atsvc_JobAdd(struct pipes_struct *p)
{
	const struct ndr_interface_call *call;
	struct ndr_pull *pull;
	struct ndr_push *push;
	enum ndr_err_code ndr_err;
	struct atsvc_JobAdd *r;

	call = &ndr_table_atsvc.calls[NDR_ATSVC_JOBADD];

	r = talloc(talloc_tos(), struct atsvc_JobAdd);
	if (r == NULL) {
		return false;
	}

	pull = ndr_pull_init_blob(&p->in_data.data, r);
	if (pull == NULL) {
		talloc_free(r);
		return false;
	}

	pull->flags |= LIBNDR_FLAG_REF_ALLOC;
	if (p->endian) {
		pull->flags |= LIBNDR_FLAG_BIGENDIAN;
	}
	ndr_err = call->ndr_pull(pull, NDR_IN, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobAdd, NDR_IN, r);
	}

	ZERO_STRUCT(r->out);
	r->out.job_id = talloc_zero(r, uint32_t);
	if (r->out.job_id == NULL) {
		talloc_free(r);
		return false;
	}

	r->out.result = _atsvc_JobAdd(p, r);

	if (p->rng_fault_state) {
		talloc_free(r);
		/* Return true here, srv_pipe_hnd.c will take care */
		return true;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobAdd, NDR_OUT | NDR_SET_VALUES, r);
	}

	push = ndr_push_init_ctx(r);
	if (push == NULL) {
		talloc_free(r);
		return false;
	}

	/*
	 * carry over the pointer count to the reply in case we are
	 * using full pointer. See NDR specification for full pointers
	 */
	push->ptr_count = pull->ptr_count;

	ndr_err = call->ndr_push(push, NDR_OUT, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	p->out_data.rdata = ndr_push_blob(push);
	talloc_steal(p->mem_ctx, p->out_data.rdata.data);

	talloc_free(r);

	return true;
}

static bool api_atsvc_JobDel(struct pipes_struct *p)
{
	const struct ndr_interface_call *call;
	struct ndr_pull *pull;
	struct ndr_push *push;
	enum ndr_err_code ndr_err;
	struct atsvc_JobDel *r;

	call = &ndr_table_atsvc.calls[NDR_ATSVC_JOBDEL];

	r = talloc(talloc_tos(), struct atsvc_JobDel);
	if (r == NULL) {
		return false;
	}

	pull = ndr_pull_init_blob(&p->in_data.data, r);
	if (pull == NULL) {
		talloc_free(r);
		return false;
	}

	pull->flags |= LIBNDR_FLAG_REF_ALLOC;
	if (p->endian) {
		pull->flags |= LIBNDR_FLAG_BIGENDIAN;
	}
	ndr_err = call->ndr_pull(pull, NDR_IN, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobDel, NDR_IN, r);
	}

	r->out.result = _atsvc_JobDel(p, r);

	if (p->rng_fault_state) {
		talloc_free(r);
		/* Return true here, srv_pipe_hnd.c will take care */
		return true;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobDel, NDR_OUT | NDR_SET_VALUES, r);
	}

	push = ndr_push_init_ctx(r);
	if (push == NULL) {
		talloc_free(r);
		return false;
	}

	/*
	 * carry over the pointer count to the reply in case we are
	 * using full pointer. See NDR specification for full pointers
	 */
	push->ptr_count = pull->ptr_count;

	ndr_err = call->ndr_push(push, NDR_OUT, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	p->out_data.rdata = ndr_push_blob(push);
	talloc_steal(p->mem_ctx, p->out_data.rdata.data);

	talloc_free(r);

	return true;
}

static bool api_atsvc_JobEnum(struct pipes_struct *p)
{
	const struct ndr_interface_call *call;
	struct ndr_pull *pull;
	struct ndr_push *push;
	enum ndr_err_code ndr_err;
	struct atsvc_JobEnum *r;

	call = &ndr_table_atsvc.calls[NDR_ATSVC_JOBENUM];

	r = talloc(talloc_tos(), struct atsvc_JobEnum);
	if (r == NULL) {
		return false;
	}

	pull = ndr_pull_init_blob(&p->in_data.data, r);
	if (pull == NULL) {
		talloc_free(r);
		return false;
	}

	pull->flags |= LIBNDR_FLAG_REF_ALLOC;
	if (p->endian) {
		pull->flags |= LIBNDR_FLAG_BIGENDIAN;
	}
	ndr_err = call->ndr_pull(pull, NDR_IN, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobEnum, NDR_IN, r);
	}

	ZERO_STRUCT(r->out);
	r->out.ctr = r->in.ctr;
	r->out.resume_handle = r->in.resume_handle;
	r->out.total_entries = talloc_zero(r, uint32_t);
	if (r->out.total_entries == NULL) {
		talloc_free(r);
		return false;
	}

	r->out.result = _atsvc_JobEnum(p, r);

	if (p->rng_fault_state) {
		talloc_free(r);
		/* Return true here, srv_pipe_hnd.c will take care */
		return true;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobEnum, NDR_OUT | NDR_SET_VALUES, r);
	}

	push = ndr_push_init_ctx(r);
	if (push == NULL) {
		talloc_free(r);
		return false;
	}

	/*
	 * carry over the pointer count to the reply in case we are
	 * using full pointer. See NDR specification for full pointers
	 */
	push->ptr_count = pull->ptr_count;

	ndr_err = call->ndr_push(push, NDR_OUT, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	p->out_data.rdata = ndr_push_blob(push);
	talloc_steal(p->mem_ctx, p->out_data.rdata.data);

	talloc_free(r);

	return true;
}

static bool api_atsvc_JobGetInfo(struct pipes_struct *p)
{
	const struct ndr_interface_call *call;
	struct ndr_pull *pull;
	struct ndr_push *push;
	enum ndr_err_code ndr_err;
	struct atsvc_JobGetInfo *r;

	call = &ndr_table_atsvc.calls[NDR_ATSVC_JOBGETINFO];

	r = talloc(talloc_tos(), struct atsvc_JobGetInfo);
	if (r == NULL) {
		return false;
	}

	pull = ndr_pull_init_blob(&p->in_data.data, r);
	if (pull == NULL) {
		talloc_free(r);
		return false;
	}

	pull->flags |= LIBNDR_FLAG_REF_ALLOC;
	if (p->endian) {
		pull->flags |= LIBNDR_FLAG_BIGENDIAN;
	}
	ndr_err = call->ndr_pull(pull, NDR_IN, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobGetInfo, NDR_IN, r);
	}

	ZERO_STRUCT(r->out);
	r->out.job_info = talloc_zero(r, struct atsvc_JobInfo *);
	if (r->out.job_info == NULL) {
		talloc_free(r);
		return false;
	}

	r->out.result = _atsvc_JobGetInfo(p, r);

	if (p->rng_fault_state) {
		talloc_free(r);
		/* Return true here, srv_pipe_hnd.c will take care */
		return true;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_FUNCTION_DEBUG(atsvc_JobGetInfo, NDR_OUT | NDR_SET_VALUES, r);
	}

	push = ndr_push_init_ctx(r);
	if (push == NULL) {
		talloc_free(r);
		return false;
	}

	/*
	 * carry over the pointer count to the reply in case we are
	 * using full pointer. See NDR specification for full pointers
	 */
	push->ptr_count = pull->ptr_count;

	ndr_err = call->ndr_push(push, NDR_OUT, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		talloc_free(r);
		return false;
	}

	p->out_data.rdata = ndr_push_blob(push);
	talloc_steal(p->mem_ctx, p->out_data.rdata.data);

	talloc_free(r);

	return true;
}


/* Tables */
static struct api_struct api_atsvc_cmds[] = 
{
	{"ATSVC_JOBADD", NDR_ATSVC_JOBADD, api_atsvc_JobAdd},
	{"ATSVC_JOBDEL", NDR_ATSVC_JOBDEL, api_atsvc_JobDel},
	{"ATSVC_JOBENUM", NDR_ATSVC_JOBENUM, api_atsvc_JobEnum},
	{"ATSVC_JOBGETINFO", NDR_ATSVC_JOBGETINFO, api_atsvc_JobGetInfo},
};

void atsvc_get_pipe_fns(struct api_struct **fns, int *n_fns)
{
	*fns = api_atsvc_cmds;
	*n_fns = sizeof(api_atsvc_cmds) / sizeof(struct api_struct);
}

NTSTATUS rpc_atsvc_init(const struct rpc_srv_callbacks *rpc_srv_cb)
{
	return rpc_srv_register(SMB_RPC_INTERFACE_VERSION, "atsvc", "atsvc", &ndr_table_atsvc, api_atsvc_cmds, sizeof(api_atsvc_cmds) / sizeof(struct api_struct), rpc_srv_cb);
}

NTSTATUS rpc_atsvc_shutdown(void)
{
	return rpc_srv_unregister(&ndr_table_atsvc);
}
