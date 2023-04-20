#include <stdio.h>

/*
软中断的处理流程：
操作系统启动后会启动一个单独的守护进程，不断轮询一组标志位
如果标志位为全 0，则挂起守护进程
如果标志位不为零，就去标志位对应的软中断向量表的相应位置，找到软中断处理函数在内存中的地址
CPU 打断当前进程的执行，转而去执行中断处理程序，执行完再返回原程序
*/

typedef struct {
    //...
    unsigned int __softirq_pending;
} irq_cpustat_t;

irq_cpustat_t irq_stat[1];

#define local_softirq_pending(cpu) (irq_stat[(cpu)].__softirq_pending) 

struct softirq_action {
    void *data;
    void (*action)(struct softirq_action *);
};

// 软中断向量表
struct softirq_action softirq_vec[32];

void do_softirq(void) {
    // 软中断向量表的基址指针
    struct softirq_action *h = softirq_vec;

    // 所有的软中断标志位
    int pending = local_softirq_pending(0);

    do {
        // 当前 bit 为 1，说明有软中断
        if (pending & 1) {
            // pending 的每一位对应 softirq_vec 的每一个元素
            // 执行对应的中断处理程序
            h->action(h);
        }

        h++;
        pending >>= 1;
    } while (pending);
}

int spawn_ksoftirqd(void) {
    // ...
    do_softirq();
    return 0;
}

void init(void) {
    spawn_ksoftirqd();
}

void reset_init(void) {
    // kernel_thread(init, NULL, CLONE_KERNEL);
    ;
}

void start_kernel(void) {
    // other init function
    reset_init();
}


/*
向软中断向量表注册中断处理程序
*/
void open_softirq(int nr, void (*action)(struct softirq_action *), void *data) {
    softirq_vec[nr].data = data;
    softirq_vec[nr].action = action;
}

enum {
    NET_TX_SOFTIRQ=0,
    NET_RX_SOFTIRQ,
};

void net_tx_softirq(struct softirq_action *h) {
    ;
}

void net_rx_softirq(struct softirq_action *h) {
    ;
}

void net_dev_init(void) {
    open_softirq(NET_TX_SOFTIRQ, net_tx_softirq, NULL);
    open_softirq(NET_RX_SOFTIRQ, net_rx_softirq, NULL);
}

int smp_processor_id(void) {
    return 0;
}

// 触发软中断
#define __raise_softirq_irqoff(nr) do { local_softirq_pending(smp_processor_id()) |= 1UL << (nr); } while(0)
