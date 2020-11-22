#pragma once
#ifndef CSeek_error
#define CSeek_error
#define CSeek_error_NULL error(0,0,"",0)
#include <cstdio>
#include "size_t.h"
#include "str.h"
#include "points.h"


struct err_out {
    points poi;
    str err;
    bool is_error;
    err_out(bool ie = 1) { is_error = ie; }
    err_out(size_t col, size_t li, const char er[], bool ie = 1) {
        poi.colum = col; poi.line = li; err = er; is_error = ie;
    }
    err_out(points p, const char er[], bool ie = 1) {
        poi=p; err = er; is_error = ie;
    }
    bool equal(err_out err) {
        return poi.colum == err.poi.colum && poi.line == err.poi.line;
    }
    void out() {
        if (!err.empty()) {
            printf(err.arr);
            char buijijijijij[255];
            char bufigigigii[255];
            snprintf(buijijijijij, 255, "%llu", poi.colum);
            snprintf(bufigigigii, 255, "%llu", poi.line);
            printf(" colum: %s, symboi: %s \n", buijijijijij, bufigigigii);
        }
    }
    void out(str er) {
        if (!er.empty()) {
            printf(er.arr);
            char buijijijijij[255];
            char bufigigigii[255];
            snprintf(buijijijijij, 255, "%llu", poi.colum);
            snprintf(bufigigigii, 255, "%llu", poi.line);
            printf(" colum: %s, symboi: %s \n", buijijijijij, bufigigigii);
        }
    }
    void out(str er, points p) {
        if (!er.empty()) {
            printf(er.arr);
            char buijijijijij[255];
            char bufigigigii[255];
            snprintf(buijijijijij, 255, "%llu", p.colum);
            snprintf(bufigigigii, 255, "%llu", p.line);
            printf(" colum: %s, symboi: %s \n", buijijijijij, bufigigigii);
        }
    }
};
/// <summary>
/// error queue
/// </summary>
struct error {
    err_out* erro = (err_out*)malloc(1*sizeof(err_out));
    points poi;
    size_t err_siz = 1;
    size_t err_use = 0;
    bool out_warns = 1;
    ~error() { free(erro); }
    void add(const char error[], points po, bool is_err) {
        if (err_siz <= err_use) {
            err_siz *= 2;
            err_out* new_s = (err_out*)malloc(err_siz * sizeof(err_out));
            if (new_s) {
                for (size_t i = 0; i < err_siz; i++)new_s[i] = erro[i];
                free(erro);
                erro = new_s;
            }
        }
        if (err_siz) erro[err_use++] = err_out(po,error,is_err);
    }
    /// <summary>
    /// write all error from queue and free it
    /// </summary>
    void out() {
        if (out_warns)
            for (size_t i = 0; i < err_use; i++)
                erro[i].out();
        else
            for (size_t i = 0; i < err_use; i++)
                if(erro[i].is_error)erro[i].out();
        free(erro);
        erro = (err_out*)malloc(err_siz * sizeof(err_out));
        err_use = 0;
    }
    void out(str er) {
        if (!er.empty()) {
            add(er.arr, poi, 1);
        }
    }
    void out(str er,points p) {
        if (!er.empty()) {
            add(er.arr, p, 1);
        }
    }
    void out(str er, int p) {
        if(p&& out_warns)
            if (!er.empty()) {
                printf(er.arr);
                char buijijijijij[255];
                char bufigigigii[255];
                snprintf(buijijijijij, 255, "%llu", poi.colum);
                snprintf(bufigigigii, 255, "%llu", poi.line);
                printf(" colum: %s, symboi: %s \n", buijijijijij, bufigigigii);
            }
    }
};
#endif // !CSeek_error_code