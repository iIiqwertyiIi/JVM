#ifndef LOGICAL_H
#define LOGICAL_H

#include <stdint.h>
#include "types.h"
#include "instructions.h"

int if_icmpeq(Frame * frame, Instruction instruction);
int iand(Frame * frame, Instruction Instruction);
int ior(Frame * frame, Instruction Instruction);
int jsr(Frame * frame, Instruction Instruction);
int jsr_w(Frame * frame, Instruction Instruction);
int ixor(Frame * frame, Instruction Instruction);
int inot(Frame * frame, Instruction Instruction);
int inot(Frame * frame, Instruction Instruction);
int if_icmpgt(Frame * frame, Instruction Instruction);
int if_icmpge(Frame * frame, Instruction Instruction);
int if_icmplt(Frame * frame, Instruction Instruction);
int if_icmple(Frame * frame, Instruction Instruction);
int if_icmpne(Frame * frame, Instruction Instruction);
int if_acmpeq(Frame * frame, Instruction Instruction);
int if_acmpne(Frame * frame, Instruction Instruction);
int ifeq(Frame * frame, Instruction Instruction);
int ifne(Frame * frame, Instruction Instruction);
int ifgt(Frame * frame, Instruction Instruction);
int ifge(Frame * frame, Instruction Instruction);
int iflt(Frame * frame, Instruction Instruction);
int ifle(Frame * frame, Instruction Instruction);
int ifnull(Frame * frame, Instruction Instruction);
int ifnonnull(Frame * frame, Instruction Instruction);
int jsr(Frame * frame, Instruction Instruction);
int jsr_w(Frame * frame, Instruction Instruction);
int goto_(Frame * frame, Instruction instruction);
int goto_w(Frame * frame, Instruction instruction);


int land(Frame * frame, Instruction instruction);
int lor(Frame * frame, Instruction instruction);
int lxor(Frame * frame, Instruction instruction);

int lcmp(Frame * frame, Instruction instruction);
int fcmpl(Frame * frame, Instruction instruction);
int fcmpg(Frame * frame, Instruction instruction);
int dcmpl(Frame * frame, Instruction instruction);
int dcmpg(Frame * frame, Instruction instruction);

#endif