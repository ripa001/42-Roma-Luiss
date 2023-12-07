import { IsString, IsNumber, IsNotEmpty, IsOptional } from 'class-validator';

export class UpdateGroupDto {

  @IsNotEmpty()
  @IsNumber()
  id: number;

	@IsNotEmpty()
	@IsString()
	name: string;
  
	@IsNotEmpty()
	@IsString()
	visibility: string;
	
	@IsOptional()
	@IsString()
	password?: string;
}
