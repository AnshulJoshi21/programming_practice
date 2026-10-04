// LOGIC GATES
module nand_gate(
  input logic a,
  input logic b,
  output logic y
);
  assign y = ~(a & b);
endmodule

module not_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  output logic [WIDTH-1:0] y
);

  genvar i;
  generate
    for (i = 0; i < WIDTH; i++) begin : not_gen
      nand_gate nand1(
        .a(a[i]),
        .b(a[i]),
        .y(y[i])
      );
    end
  endgenerate;

endmodule

module and_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] nand_out;

  genvar i;
  generate
    for (i = 0; i < WIDTH; i++) begin : not_gen
      nand_gate nand1(
        .a(a[i]),
        .b(b[i]),
        .y(nand_out[i])
      );
    end
  endgenerate;

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(nand_out),
    .y(y)
  );

endmodule

module or_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] not_a;
  logic [WIDTH-1:0] not_b;

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(a),
    .y(not_a)
  );

  not_gate #(.WIDTH(WIDTH)) not2(
    .a(b),
    .y(not_b)
  );

  genvar i;
  generate
    for (i = 0; i < WIDTH; i++) begin : or_gen
      nand_gate nand1(
        .a(not_a[i]),
        .b(not_b[i]),
        .y(y[i])
      );
    end
  endgenerate

endmodule

module xor_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] not_a;
  logic [WIDTH-1:0] not_b;

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(a),
    .y(not_a)
  );

  not_gate #(.WIDTH(WIDTH)) not2(
    .a(b),
    .y(not_b)
  );

  logic [WIDTH-1:0] and1_out;
  logic [WIDTH-1:0] and2_out;

  and_gate #(.WIDTH(WIDTH)) and1(
    .a(not_a),
    .b(b),
    .y(and1_out)
  );

  and_gate #(.WIDTH(WIDTH)) and2(
    .a(a),
    .b(not_b),
    .y(and2_out)
  );

  or_gate #(.WIDTH(WIDTH)) or1(
    .a(and1_out),
    .b(and2_out),
    .y(y)
  );
  
endmodule


// ADDERS
module half_adder(
  input logic a, 
  input logic b,
  output logic sum,
  output logic cout
);

  xor_gate #(.WIDTH(1)) xor_gate(
    .a(a),
    .b(b),
    .y(sum)
  );

  and_gate #(.WIDTH(1)) and_gate(
    .a(a),
    .b(b),
    .y(cout)
  );

endmodule

module full_adder #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  input logic cin,
  output logic [WIDTH-1:0] sum,
  output logic cout
);


  logic [WIDTH-1:0] ha1_sum;
  logic [WIDTH-1:0] ha1_cout;
  logic [WIDTH-1:0] ha2_cout;

  logic [WIDTH:0] main_cout;
  assign main_cout[0] = cin;

  genvar i;
  generate
    for (i = 0; i < WIDTH; i++) begin
      half_adder ha1(
        .a(a[i]),
        .b(b[i]),
        .sum(ha1_sum[i]),
        .cout(ha1_cout[i])
      );

      half_adder ha2(
        .a(ha1_sum[i]),
        .b(main_cout[i]),
        .sum(sum[i]),
        .cout(ha2_cout[i])
      );

      or_gate #(.WIDTH(1)) or1(
        .a(ha1_cout[i]),
        .b(ha2_cout[i]),
        .y(main_cout[i + 1])
      );
            
    end
  endgenerate

  assign cout = main_cout[WIDTH];

endmodule

// // MUXES
module mux_2x1(
  input logic sel,
  input logic [1:0] data,
  output logic y
);

  logic not_sel;
  not_gate #(.WIDTH(1)) not1(
    .a(sel),
    .y(not_sel)
  );

  logic and1_out;
  logic and2_out;

  and_gate #(.WIDTH(1)) and1(
    .a(not_sel),
    .b(data[0]),
    .y(and1_out)
  );

  and_gate #(.WIDTH(1)) and2(
    .a(sel),
    .b(data[1]),
    .y(and2_out)
  );

  or_gate #(.WIDTH(1)) or1(
    .a(and1_out),
    .b(and2_out),
    .y(y)
  );

endmodule

module mux_4x1(
  input logic [1:0] sel,
  input logic [3:0] data,
  output logic y
);

  logic m1_out;
  logic m2_out;

  mux_2x1 m1(
    .sel(sel[0]),
    .data(data[1:0]),
    .y(m1_out)
  );

  mux_2x1 m2(
    .sel(sel[0]),
    .data(data[3:2]),
    .y(m2_out)
  );

  mux_2x1 m3(
    .sel(sel[1]),
    .data({m2_out, m1_out}),
    .y(y)
  );

endmodule

module mux_8x1(
  input logic [2:0] sel,
  input logic [7:0] data,
  output logic y
);

  logic m1_out;
  logic m2_out;

  mux_4x1 m1(
    .sel(sel[1:0]),
    .data(data[3:0]),
    .y(m1_out)
  );

  mux_4x1 m2(
    .sel(sel[1:0]),
    .data(data[7:4]),
    .y(m2_out)
  );

  mux_2x1 m3(
    .sel(sel[2]),
    .data({m2_out, m1_out}),
    .y(y)
  );

endmodule

// DEMUX
module dmux_1x2(
  input logic sel,
  input logic data,
  output logic [1:0] y
);

  logic not_sel;
  not_gate #(.WIDTH(1)) not1(
    .a(sel),
    .y(not_sel)
  );

  and_gate #(.WIDTH(1)) and1(
    .a(not_sel),
    .b(data),
    .y(y[0])
  );

  and_gate #(.WIDTH(1)) and2(
    .a(sel),
    .b(data),
    .y(y[1])
  );

endmodule

module dmux_1x4(
  input logic [1:0] sel,
  input logic data,
  output logic [3:0] y
);

  logic [1:0] dm1_out;

  dmux_1x2 dm1(
    .sel(sel[1]),
    .data(data),
    .y(dm1_out)
  );

  dmux_1x2 dm2(
    .sel(sel[0]),
    .data(dm1_out[0]),
    .y(y[1:0])
  );

  dmux_1x2 dm3(
    .sel(sel[0]),
    .data(dm1_out[1]),
    .y(y[3:2])
  );

endmodule

module dmux_1x8(
  input logic [2:0] sel,
  input logic data,
  output logic [7:0] y
);

  logic [1:0] dm1_out;

  dmux_1x2 dm1(
    .sel(sel[2]),
    .data(data),
    .y(dm1_out)
  );

  dmux_1x4 dm2(
    .sel(sel[1:0]),
    .data(dm1_out[0]),
    .y(y[3:0])
  );

  dmux_1x4 dm3(
    .sel(sel[1:0]),
    .data(dm1_out[1]),
    .y(y[7:4])
  );

endmodule

// BASIC OPERATION
module add #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] sum,
  output logic cout
);

  full_adder #(.WIDTH(WIDTH)) fa(
    .a(a),
    .b(b),
    .cin(1'b0),
    .sum(sum),
    .cout(cout)
  );

endmodule

module sub #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] sum,
  output logic cout
);

  logic [WIDTH-1:0] not_b;
  not_gate #(.WIDTH(WIDTH)) not1(
    .a(b),
    .y(not_b)
  );

  full_adder #(.WIDTH(WIDTH)) fa(
    .a(a),
    .b(not_b),
    .cin(1'b1),
    .sum(sum),
    .cout(cout)
  );

endmodule

module shl #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  output logic [WIDTH-1:0] y,
  output logic cout
);

  genvar i;
  generate
    for (i = 1; i < WIDTH; i++) begin
      assign y[i] = a[i - 1];
    end
  endgenerate

  assign y[0] = 1'b0;
  assign cout = a[WIDTH-1];

endmodule


module shr #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  output logic [WIDTH-1:0] y,
  output logic cout
);

  genvar i;
  generate
    for (i = 0; i < WIDTH - 1; i++) begin
      assign y[i] = a[i + 1];
    end
  endgenerate

  assign y[WIDTH-1] = 1'b0;
  assign cout = a[0];

endmodule

// ALU
module alu8(
  input logic [2:0] opcode, // opcode
  input logic [7:0] a,
  input logic [7:0] b,
  output logic [7:0] y,
  output logic carry,
  output logic sign,
  output logic zero,
  output logic overflow
);

  logic [7:0] add_sum;
  logic add_cout;
  logic [7:0] sub_sum;
  logic sub_cout;

  logic [7:0] shl_y;
  logic shl_cout;
  logic [7:0] shr_y;
  logic shr_cout;

  logic [7:0] and_y;
  logic [7:0] or_y;
  logic [7:0] xor_y;
  logic [7:0] not_y;

  // basic operations 
  add #(.WIDTH(8)) add1(
    .a(a),
    .b(b),
    .sum(add_sum),
    .cout(add_cout)
  );

  sub #(.WIDTH(8)) sub1(
    .a(a),
    .b(b),
    .sum(sub_sum),
    .cout(sub_cout)
  );

  and_gate #(.WIDTH(8)) and1(
    .a(a),
    .b(b),
    .y(and_y)
  );

  or_gate #(.WIDTH(8)) or1(
    .a(a),
    .b(b),
    .y(or_y)
  );

  xor_gate #(.WIDTH(8)) xor1(
    .a(a),
    .b(b),
    .y(xor_y)
  );

  not_gate #(.WIDTH(8)) not1(
    .a(a),
    .y(not_y)
  );

  shl #(.WIDTH(8)) shl1(
    .a(a),
    .y(shl_y),
    .cout(shl_cout)
  );

  shr #(.WIDTH(8)) shr1(
    .a(a),
    .y(shr_y),
    .cout(shr_cout)
  );

  // y calculation
  logic [7:0] result_y;
  
  genvar i;
  generate
    for (i = 0; i < 8; i++) begin

      // NOTE: parameterize mux later
      mux_8x1 mux1(
        .sel(opcode),
        .data(
          {add_sum[i],
          sub_sum[i],
          and_y[i],
          or_y[i],
          xor_y[i],
          not_y[i],
          shl_y[i],
          shr_y[i]}
        ),
        .y(y[i])
      );

    end
  endgenerate

  // carry calculation
  mux_8x1 mux2(
    .sel(opcode),
    .data(
      {add_cout,
      sub_cout,
      1'b0, // no carry operation
      1'b0, // no carry operation
      1'b0, // no carry operation
      1'b0, // no carry operation
      shl_cout,
      shr_cout}
    ),
    .y(carry)
  );

  // sign
  assign sign = y[7];

  // zero calculation
  logic [8:0] temp_zero;
  assign temp_zero[0] = 1'b1;

  logic [7:0] not2_y;
  not_gate #(.WIDTH(8)) not2(
    .a(y),
    .y(not2_y)
  );

  generate
    for (i = 0; i < 8; i++) begin
      and_gate #(.WIDTH(1)) and2(
        .a(temp_zero[i]),
        .b(not2_y[i]),
        .y(temp_zero[i + 1])
      );
    end
  endgenerate

  assign zero = temp_zero[8];

  // overflow calculation
  logic xor_msb_ab;
  logic xnor_msb_ab;
  logic xor_msb_ay;

  xor_gate #(.WIDTH(1)) xor2(
    .a(a[7]),
    .b(b[7]),
    .y(xor_msb_ab)
  );

  xor_gate #(.WIDTH(1)) xor3(
    .a(a[7]),
    .b(y[7]),
    .y(xor_msb_ay)
  );

  not_gate #(.WIDTH(1)) not3(
    .a(xor_msb_ab),
    .y(xnor_msb_ab)
  );

  logic overflow_add;
  logic overflow_sub;

  and_gate #(.WIDTH(1)) and3(
    .a(xnor_msb_ab),
    .b(xor_msb_ay),
    .y(overflow_add)
  );

  and_gate #(.WIDTH(1)) and4(
    .a(xor_msb_ab),
    .b(xor_msb_ay),
    .y(overflow_sub)
  );

  logic overflow_selected;
  mux_2x1 mux3(
    .sel(opcode[0]),
    .data({overflow_sub, overflow_add}),
    .y(overflow_selected)
  );

  logic not_op2;
  logic not_op1;
  not_gate #(.WIDTH(1)) not4(
    .a(opcode[2]),
    .y(not_op2)
  );

  not_gate #(.WIDTH(1)) not5(
    .a(opcode[1]),
    .y(not_op1)
  );

  logic is_arith;
  and_gate #(.WIDTH(1)) and5(
    .a(not_op2),
    .b(not_op1),
    .y(is_arith)
  );
  
  // main overflow
  and_gate #(.WIDTH(1)) and6(
    .a(is_arith),
    .b(overflow_selected),
    .y(overflow)
  );

endmodule
