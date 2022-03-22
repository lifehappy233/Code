package main

import "fmt"

var a []int64

var f [][]int64

var n, m, k int

func main() {
	fmt.Scanf("%d %d %d", &n, &m, &k)
	a = make([]int64, n+10)
	f = make([][]int64, n+10)
	f[0] = make([]int64, k+10)

	for i := 1; i <= n; i++ {
		fmt.Scanf("%d", &a[i])
		a[i] += a[i-1]
	}

	for i := 1; i <= n; i++ {
		f[i] = make([]int64, k+10)
		for j := 1; j <= min(i/m, k); j++ {
			f[i][j] = max(f[i][j], f[i-1][j])
			f[i][j] = max(f[i][j], f[i-m][j-1]+a[i]-a[i-m])
		}
	}
	fmt.Println(f[n][k])
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}
