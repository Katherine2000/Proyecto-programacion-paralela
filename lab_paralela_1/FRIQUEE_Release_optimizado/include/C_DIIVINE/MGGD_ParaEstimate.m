function [alpha, beta] = MGGD_ParaEstimate(x)

m1 = mean(x);
m2 = mean(x.^2);
gam = 0.1:0.001:10;
beta_gam = (gamma(3./gam).^2)./(gamma(2./gam).*gamma(4./gam));
rho_x = (m1^2)/m2;
[beta_diff, beta_ind] = min(abs(rho_x - beta_gam));
beta_0 = beta_gam(beta_ind);
a_ = log(x);
b_ = length(x);

for itr = 1:500
    if itr == 500
        error('data do not converge');
        %alpha = 0; beta = 0;
    end
    beta_old = beta_0;
%     if(beta_0 < 0)
%         beta_0 = 0;
%     end
%     
    [f0, f1] = f(beta_0, x,a_,b_);
    beta_new = beta_0 - f0/f1;
    beta_0 = beta_new;
    if abs(beta_new - beta_old) < 0.0001
        beta = beta_new;
        break;
    end    
end
N = length(x);
alpha = (0.5*beta*sum(x.^beta)/N)^(1/beta);

function [f0, f1] = f(b, r,a_,b_)
k = (r.^b);
t = (2/b);
r_b = sum(k);
ss = a_;

N = b_;
j = b * r_b;
pp = psi(t);
rr = log(0.5*j/N);
r_b_log = sum(ss.* k);
r_b_log2 = sum(ss.*ss.* k);
f0 = 1 + 2*pp/b - 2*r_b_log/r_b + (t) * rr;

q = (b^2);
A = -2*pp/q - 4*psi(1,t)/(b^3);
B = -2*(r_b_log2 * r_b - r_b_log^2)/(r_b^2);
C = -2*rr/q + 2/q + 2*r_b_log/(j);

f1 = A + B + C;






