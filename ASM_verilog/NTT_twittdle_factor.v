module twiddle_factor_table(len)
input [5:0] len;
reg [5:0] pre_value = 4;
//twiddle factor table
reg [63:0] ntt_twiddle_table [63:0][63:0];
						//make first index 0-63 , index two
//for loop to clean first index to 0 

module rst_counter(clk,len,rst,pre_value,counter_x , counter_y)
	
	reg [63:0] p = 4179340454199820289;
	reg [63:0] omega = 68630377364883;
	reg [63:0] m = 57;
	reg [9:0] counter_x;
	reg [9:0] counter_y;
	reg [9:0] iterator;
	reg [9:0] current_process;
	reg set_enable;
	always @(!set_enable)
	begin
		current_process = current_process - 1;
		if (current_process == pre_value)
		begin
			pre_value = iterator;
		end
		if (len > iterator)
		begin
			iterator = len;
			current_process = len;
		end
		if (current_process > pre_value)
		begin
			set_enable = 1;
		end
	end
	always @(!set_enable)
	begin
		if (counter_y == 0)
		begin
			sliced_ntt_twiddle_table[counter_x][counter_y] <= 0;
		end
		else if(counter_y == 1)
		begin
			//special modexp not yet implemented
		end
		else
		begin
			//two case if iterator is bigger than current_process , use half of the previous value (bigger one)
			/*
				for method 1 , how to acquire another slice?
			*////

			//second case ,  the 
		end
	end
module set_counter(set_enable , rst , iterator ,counter_x , counter_y , sliced_ntt_twiddle_table ,len)
	always @(set_enable)
	begin
		if(rst)
		begin
			counter_x <= 0;
			counter_y <= 0;
		end
		else
		begin
			counter_y <= counter_y +1 ;
			if (counter_y > len)
			begin
				counter_x <= counter_x + 1;
				counter_y <= 0;
			end
		end
	end
end