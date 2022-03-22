package main

import "fmt"

type Work interface {
	value()
}

type noneWork int

func (n *noneWork) value() {
	fmt.Println("None")
}

type keyWork struct {
	Work
	msg string
}

func (k *keyWork) value() {
	fmt.Println(k.msg)
	k.Work.value()
}

func withKeyWork(parent Work, msg string) Work {
	return &keyWork{parent, msg}
}

func main() {
	root := new(noneWork)
	a := withKeyWork(root, "a")
	b := withKeyWork(a, "b")
	a.value()
	b.value()
}
