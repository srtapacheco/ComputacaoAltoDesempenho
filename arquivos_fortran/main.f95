program main
  implicit none
  integer, parameter :: dp = selected_real_kind(15, 307)
  integer :: n, i, j
  real(dp), allocatable :: A(:,:), x(:), b(:)
  real(dp) :: start_time, end_time, elapsed_time

  ! Tamanho do sistema
  n = 1000

  ! Aloca a matriz A e os vetores x e b
  allocate(A(n,n), x(n), b(n))

  ! Inicializa A, x e b com valores aleatórios
  call random_number(A)
  call random_number(x)
  call random_number(b)

  ! Mede o tempo de execução do produto matriz-vetor
  call cpu_time(start_time)
  do i = 1, n
    b(i) = 0.0_dp
    do j = 1, n
      b(i) = b(i) + A(i,j) * x(j)
    end do
  end do
  call cpu_time(end_time)

  elapsed_time = end_time - start_time

  print *, "Tempo de execução:", elapsed_time, "segundos"

  ! Libera a memória alocada
  deallocate(A, x, b)

end program main
