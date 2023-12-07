import { PartialType } from "@nestjs/swagger"
import { CreateFrienshipDto } from "./create-frienship.dto"

export class UpdateFrienshipDto extends CreateFrienshipDto {

	// the suer sending the update friendship message
	bearerID: number


	are_friends: boolean
	pending_friendship: boolean
	requestor_blacklisted: boolean
	recipient_blacklisted: boolean
}
