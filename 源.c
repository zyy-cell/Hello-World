#include<stdio.h>
#include<omp.h>
double sum_time = 0.0;
double global_result = 0.0;
void Trap(double q, double w, int e)
//���һ�����������ǵ�ַ�������̰߳Ѽ�����ͨ����ַ��esult��ʽ�ۼӡ�ԭ����������������ǵ�ַ������Ӳ������棬��globab_result��ֵ���䡣
{
	double h, x, my_result;
	double local_a, local_b;
	int i, local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	double my_start, my_finish,my_time;
	my_start = omp_get_wtime();
	h = (w - q) / e;
	local_n = e / thread_count;
	local_a = q + my_rank * local_n*h;
	local_b = local_a + local_n * h;
	my_result = (local_a*local_a + local_b * local_b) / 2.0;
	for (i = 1; i < local_n; i++)
	{
		x = local_a + h * i;
		my_result = my_result + x * x;
	}
	my_result = my_result * h;
	my_finish = omp_get_wtime();
	my_time = my_finish - my_start;
	printf("%d thread result=%lf    time=%e\n", my_rank, my_result,my_time);
#pragma omp critical
	{
		global_result += my_result;
		sum_time += my_time;
	}

}
int main()
{
	double a, b;//�������˱�������������ʱ����Ҫ����ñ�����ֵʱ����scanf��Ҫ�������������Ӧ����������
	int n;
	int thread_count = 4;
	double start, finish, time;
	printf("Enter a,b,and n\n");
	scanf("%lf %lf %d", &a, &b, &n);//���Դ˴��������a��bʱ����ʽ��ΪдΪ%lf������%f����������
	start = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
	Trap(a, b, n);
	finish = omp_get_wtime();
	time = finish - start;
	printf("������Ϊ��%e,����ʱ��Ϊ��%e\n",global_result,time);
	printf("���߳�ʱ��֮��Ϊ��%e", sum_time);
	system("pause");
	return 0;
}
