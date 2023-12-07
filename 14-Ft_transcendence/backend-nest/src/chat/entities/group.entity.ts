import { IsArray, IsString, IsInt, IsBoolean, IsNotEmpty, IsOptional } from 'class-validator';


export class Group {
	@IsNotEmpty()
	@IsString()
	name: string;
  
	@IsNotEmpty()
	@IsInt({ each: true })
	members: number[];
  
	@IsNotEmpty()
	@IsInt()
	founderId: number;
  
	@IsNotEmpty()
	@IsString()
	visibility: string;
	
	@IsOptional()
	@IsString()
	password?: string;
}
