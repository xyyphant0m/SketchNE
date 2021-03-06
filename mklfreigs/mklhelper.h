#pragma once
#include <cstdint>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "mkl.h"
#include "mkl_cblas.h"

#define SEED    777
#define BRNG VSL_BRNG_SFMT19937
//#define BRNG    VSL_BRNG_MCG31
#define METHOD VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2
//#define METHOD VSL_RNG_METHOD_GAUSSIAN_ICDF

template <typename T>
struct mklhelper {};


template <>
struct mklhelper<float> {
    
    static int vRngGaussian(const MKL_INT method, VSLStreamStatePtr stream, const MKL_INT n, float* r, const float a, const float sigma) {
        return vsRngGaussian(method, stream, n, r, a, sigma);
    }
    static lapack_int LAPACKE_geqrf(int matrix_layout, lapack_int m, lapack_int n, float* a, lapack_int lda, float* tau) {
        return LAPACKE_sgeqrf(matrix_layout, m, n, a, lda, tau);
    }
    static lapack_int LAPACKE_geqpf (int matrix_layout, lapack_int m, lapack_int n, float* a,lapack_int lda, lapack_int* jpvt, float* tau){
        return LAPACKE_sgeqpf (matrix_layout, m, n, a, lda, jpvt, tau);
    }
    static lapack_int LAPACKE_orgqr(int matrix_layout, lapack_int m, lapack_int n, lapack_int k, float* a, lapack_int lda, const float* tau) {
        return LAPACKE_sorgqr(matrix_layout, m, n, k, a, lda, tau);
    }
    static lapack_int LAPACKE_syev (int matrix_layout, char jobz, char uplo, lapack_int n, float* a, lapack_int lda, float* w){
        return LAPACKE_ssyev (matrix_layout, jobz, uplo, n, a, lda, w);
    }
    static lapack_int LAPACKE_syevd (int matrix_layout, char jobz, char uplo, lapack_int n, float* a, lapack_int lda, float* w){
        return LAPACKE_ssyevd (matrix_layout, jobz, uplo, n, a, lda, w);
    }

    static lapack_int LAPACKE_gesvd(int matrix_layout, char jobu, char jobvt, lapack_int m, lapack_int n, float* a, lapack_int lda, float* s, float* u, lapack_int ldu, float* vt, lapack_int ldvt, float* superb ) {
        return LAPACKE_sgesvd(matrix_layout, jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, superb );
    }
    static lapack_int LAPACKE_gesdd(int matrix_layout, char jobz, lapack_int m, lapack_int n,float* a, lapack_int lda, float* s, float* u, lapack_int ldu, float* vt, lapack_int ldvt) {
        return LAPACKE_sgesdd(matrix_layout, jobz, m, n, a, lda, s, u, ldu, vt, ldvt);
    }
    static lapack_int LAPACKE_getrf (int matrix_layout , lapack_int m , lapack_int n , float * a , lapack_int lda , lapack_int * ipiv ){
        return LAPACKE_sgetrf (matrix_layout, m, n, a, lda, ipiv );
    }
    static lapack_int LAPACKE_getrs (int matrix_layout , char trans , lapack_int n , lapack_int nrhs , const float * a , lapack_int lda , const lapack_int * ipiv , float * b ,lapack_int ldb ){
        return LAPACKE_sgetrs (matrix_layout, trans, n, nrhs, a, lda, ipiv, b, ldb);
    }
    static lapack_int LAPACKE_trtrs (int matrix_layout , char uplo , char trans , char diag , lapack_int n , lapack_int nrhs , const float * a , lapack_int lda , float * b , lapack_int ldb ){
        return LAPACKE_strtrs(matrix_layout, uplo, trans, diag, n, nrhs, a, lda, b, ldb );
    }

    static void cblas_gemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE transa, const CBLAS_TRANSPOSE transb, const MKL_INT m, const MKL_INT n, const MKL_INT k, const float alpha, const float *a, const MKL_INT lda, const float *b, const MKL_INT ldb, const float beta, float *c, const MKL_INT ldc) {
        cblas_sgemm(Layout, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }
    
    static void cblas_axpy(const MKL_INT n, const float a, const float *x, const MKL_INT incx, float *y, const MKL_INT incy) {
        cblas_saxpy(n, a, x, incx, y, incy);
    }
    static void cblas_axpby(const MKL_INT n, const float alpha, const float *x, const MKL_INT incx, const float beta, float *y, const MKL_INT incy) {
        cblas_saxpby(n, alpha, x, incx, beta, y, incy);
    }

    static void cblas_copy(const MKL_INT n, const float *x, const MKL_INT incx, float *y, const MKL_INT incy) {
        cblas_scopy(n, x, incx, y, incy);
    }
    static float cblas_nrm2(const MKL_INT n, const float *x, const MKL_INT incx) {
        return cblas_snrm2(n, x, incx);
    }

    static void cblas_scal(const MKL_INT n, const float a, float *x, const MKL_INT incx) {
        cblas_sscal(n, a, x, incx);
    }
    
    static void mkl_csrmm (const char *transa , const MKL_INT *m , const MKL_INT *n , const MKL_INT *k , const float *alpha , const char *matdescra , const float *val , const MKL_INT *indx , const MKL_INT *pntrb , const MKL_INT *pntre , const float *b , const MKL_INT *ldb , const float *beta , float *c , const MKL_INT *ldc ){
        mkl_scsrmm (transa, m, n, k, alpha, matdescra, val, indx, pntrb, pntre, b, ldb, beta, c, ldc);
    }
    static sparse_status_t mkl_sparse_create_coo(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, const MKL_INT nnz, MKL_INT *row_indx, MKL_INT *col_indx, float *values) {
        return mkl_sparse_s_create_coo(A, indexing, rows, cols, nnz, row_indx, col_indx, values);
    }
    static sparse_status_t mkl_sparse_create_csc(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, MKL_INT *cols_start, MKL_INT *cols_end, MKL_INT *row_indx, float *values) {
        return mkl_sparse_s_create_csc(A, indexing, rows, cols,cols_start, cols_end, row_indx, values);
    }
    static sparse_status_t mkl_sparse_create_csr(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, MKL_INT *rows_start, MKL_INT *rows_end, MKL_INT *col_indx, float *values) {
        return mkl_sparse_s_create_csr(A, indexing, rows, cols, rows_start, rows_end, col_indx, values);
    }
    static sparse_status_t mkl_sparse_mm(const sparse_operation_t operation, const float alpha, const sparse_matrix_t A, const struct matrix_descr descr, const sparse_layout_t layout, const float *x, const MKL_INT columns, const MKL_INT ldx, const float beta, float *y, const MKL_INT ldy) {
        return mkl_sparse_s_mm(operation, alpha, A, descr, layout, x, columns, ldx, beta, y, ldy);
    }
    static sparse_status_t mkl_sparse_spmmd(const sparse_operation_t operation,const sparse_matrix_t A,const sparse_matrix_t B,const sparse_layout_t layout, float *C,const MKL_INT ldc ) {
        return mkl_sparse_s_spmmd(operation, A, B, layout, C, ldc);
    }
    static sparse_status_t mkl_sparse_sp2md(const sparse_operation_t transA, const struct matrix_descr descrA, const sparse_matrix_t A, const sparse_operation_t transB, const struct matrix_descr descrB, const sparse_matrix_t B, const float alpha, const float beta, float *C, const sparse_layout_t layout, const MKL_INT ldc ) {
        return mkl_sparse_s_sp2md(transA, descrA, A, transB, descrB, B, alpha, beta, C, layout, ldc );
    }
};



template <>
struct mklhelper<double> {
  
    static int vRngGaussian(const MKL_INT method, VSLStreamStatePtr stream, const MKL_INT n, double* r, const double a, const double sigma) {
        return vdRngGaussian(method, stream, n, r, a, sigma);
    }
    static lapack_int LAPACKE_geqrf(int matrix_layout, lapack_int m, lapack_int n, double* a, lapack_int lda, double* tau) {
        return LAPACKE_dgeqrf(matrix_layout, m, n, a, lda, tau);
    }
    static lapack_int LAPACKE_geqpf (int matrix_layout, lapack_int m, lapack_int n, float* a,lapack_int lda, lapack_int* jpvt, float* tau){
        return LAPACKE_sgeqpf (matrix_layout, m, n, a, lda, jpvt, tau);
    }
    static lapack_int LAPACKE_orgqr(int matrix_layout, lapack_int m, lapack_int n, lapack_int k, double* a, lapack_int lda, const double* tau) {
        return LAPACKE_dorgqr(matrix_layout, m, n, k, a, lda, tau);
    }
    static lapack_int LAPACKE_syev (int matrix_layout, char jobz, char uplo, lapack_int n, double* a, lapack_int lda, double* w){
        return LAPACKE_dsyev (matrix_layout, jobz, uplo, n, a, lda, w);
    }
    static lapack_int LAPACKE_syevd (int matrix_layout, char jobz, char uplo, lapack_int n, double* a, lapack_int lda, double* w){
        return LAPACKE_dsyevd (matrix_layout, jobz, uplo, n, a, lda, w);
    }
    static lapack_int LAPACKE_gesvd(int matrix_layout, char jobu, char jobvt, lapack_int m, lapack_int n, double* a, lapack_int lda, double* s, double* u, lapack_int ldu, double* vt, lapack_int ldvt, double* superb ) {
        return LAPACKE_dgesvd(matrix_layout, jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, superb );
    }
    static lapack_int LAPACKE_gesdd(int matrix_layout, char jobz, lapack_int m, lapack_int n,double* a, lapack_int lda, double* s, double* u, lapack_int ldu, double* vt, lapack_int ldvt) {
        return LAPACKE_dgesdd(matrix_layout, jobz, m, n, a, lda, s, u, ldu, vt, ldvt);
    }
    static lapack_int LAPACKE_getrf (int matrix_layout , lapack_int m , lapack_int n , double * a , lapack_int lda , lapack_int * ipiv ){
        return LAPACKE_dgetrf (matrix_layout, m, n, a, lda, ipiv );
    }
    static lapack_int LAPACKE_getrs (int matrix_layout , char trans , lapack_int n , lapack_int nrhs , const double * a , lapack_int lda , const lapack_int * ipiv , double * b ,lapack_int ldb ){
        return LAPACKE_dgetrs (matrix_layout, trans, n, nrhs, a, lda, ipiv, b, ldb);
    }
    static lapack_int LAPACKE_trtrs (int matrix_layout , char uplo , char trans , char diag , lapack_int n , lapack_int nrhs , const double * a , lapack_int lda , double * b , lapack_int ldb ){
        return LAPACKE_dtrtrs(matrix_layout, uplo, trans, diag, n, nrhs, a, lda, b, ldb );
    }

    static void cblas_gemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE transa, const CBLAS_TRANSPOSE transb, const MKL_INT m, const MKL_INT n, const MKL_INT k, const double alpha, const double *a, const MKL_INT lda, const double *b, const MKL_INT ldb, const double beta, double *c, const MKL_INT ldc) {
        cblas_dgemm(Layout, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    static void cblas_axpy(const MKL_INT n, const double a, const double *x, const MKL_INT incx, double *y, const MKL_INT incy) {
        cblas_daxpy(n, a, x, incx, y, incy);
    }

    static void cblas_axpby(const MKL_INT n, const double alpha, const double *x, const MKL_INT incx, const double beta, double *y, const MKL_INT incy) {
        cblas_daxpby(n, alpha, x, incx, beta, y, incy);
    }

    static void cblas_copy(const MKL_INT n, const double *x, const MKL_INT incx, double *y, const MKL_INT incy) {
        cblas_dcopy(n, x, incx, y, incy);
    }

    static double cblas_nrm2(const MKL_INT n, const double *x, const MKL_INT incx) {
        return cblas_dnrm2(n, x, incx);
    }

    static void cblas_scal(const MKL_INT n, const double a, double *x, const MKL_INT incx) {
        cblas_dscal(n, a, x, incx);
    }

    static void mkl_csrmm (const char *transa , const MKL_INT *m , const MKL_INT *n , const MKL_INT *k , const double *alpha , const char *matdescra , const double *val , const MKL_INT *indx , const MKL_INT *pntrb , const MKL_INT *pntre , const double *b , const MKL_INT *ldb , const double *beta , double *c , const MKL_INT *ldc ){
        mkl_dcsrmm (transa, m, n, k, alpha, matdescra, val, indx, pntrb, pntre, b, ldb, beta, c, ldc);
    }

    static sparse_status_t mkl_sparse_create_coo(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, const MKL_INT nnz, MKL_INT *row_indx, MKL_INT *col_indx, double *values) {
        return mkl_sparse_d_create_coo(A, indexing, rows, cols, nnz, row_indx, col_indx, values);
    }
    static sparse_status_t mkl_sparse_create_csc(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, MKL_INT *cols_start, MKL_INT *cols_end, MKL_INT *row_indx, double *values) {
        return mkl_sparse_d_create_csc(A, indexing, rows, cols,cols_start, cols_end, row_indx, values);
    }
    static sparse_status_t mkl_sparse_create_csr(sparse_matrix_t *A, const sparse_index_base_t indexing, const MKL_INT rows, const MKL_INT cols, MKL_INT *rows_start, MKL_INT *rows_end, MKL_INT *col_indx, double *values) {
        return mkl_sparse_d_create_csr(A, indexing, rows, cols, rows_start, rows_end, col_indx, values);
    }
    static sparse_status_t mkl_sparse_mm(const sparse_operation_t operation, const double alpha, const sparse_matrix_t A, const struct matrix_descr descr, const sparse_layout_t layout, const double *x, const MKL_INT columns, const MKL_INT ldx, const double beta, double *y, const MKL_INT ldy) {
        return mkl_sparse_d_mm(operation, alpha, A, descr, layout, x, columns, ldx, beta, y, ldy);
    }
    static sparse_status_t mkl_sparse_spmmd(const sparse_operation_t operation,const sparse_matrix_t A,const sparse_matrix_t B,const sparse_layout_t layout, double *C,const MKL_INT ldc ) {
        return mkl_sparse_d_spmmd(operation, A, B, layout, C, ldc);
    }
    static sparse_status_t mkl_sparse_sp2md(const sparse_operation_t transA, const struct matrix_descr descrA, const sparse_matrix_t A, const sparse_operation_t transB, const struct matrix_descr descrB, const sparse_matrix_t B, const double alpha, const double beta, double *C, const sparse_layout_t layout, const MKL_INT ldc) {
        return mkl_sparse_d_sp2md(transA, descrA, A, transB, descrB, B, alpha, beta, C, layout, ldc );
    }

};
