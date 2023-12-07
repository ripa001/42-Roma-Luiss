
--- Inserting Achievements
INSERT INTO "Achievement" (
	"createdAt",
	"updatedAt",
	"name",
	"description",
	"picture"
)
VALUES (
	CURRENT_TIMESTAMP,
	CURRENT_TIMESTAMP,
	'promising kitty',
	'You have won one game, congratulations!',
	'https://www.eltekitalia.it/portal/wp-content/uploads/2023/12/cat_portrait_by_elit3workshop_dfisg7r-414w-2x.jpg'
)
ON CONFLICT DO NOTHING;

INSERT INTO "Achievement" (
	"createdAt",
	"updatedAt",
	"name",
	"description",
	"picture"
)
VALUES (
	CURRENT_TIMESTAMP,
	CURRENT_TIMESTAMP,
	'Now feed me some good tuna!',
	'You have won two games, congratulations!',
	'https://www.eltekitalia.it/portal/wp-content/uploads/2023/12/adventurous_cat_on_a_mountain_by_eleazatlr_dfm6xoc-pre.jpg'
)
ON CONFLICT DO NOTHING;

INSERT INTO "Achievement" (
	"createdAt",
	"updatedAt",
	"name",
	"description",
	"picture"
)
VALUES (
	CURRENT_TIMESTAMP,
	CURRENT_TIMESTAMP,
	'I need no Catnip to win!',
	'You have won five games, congratulations!',
	'https://www.eltekitalia.it/portal/wp-content/uploads/2023/12/helghast_cat_2_by_easycheuvreuille_d7kqif4-pre.jpg'
)
ON CONFLICT DO NOTHING;

INSERT INTO "Achievement" (
	"createdAt",
	"updatedAt",
	"name",
	"description",
	"picture"
)
VALUES (
	CURRENT_TIMESTAMP,
	CURRENT_TIMESTAMP,
	'Your Catventure begins here!',
	'You successfully created a profile @ cazzendence!',
	'https://www.eltekitalia.it/portal/wp-content/uploads/2023/12/art_deco_cat_by_aleyarts_dfnr4sy-375w-2x.jpg'
)
ON CONFLICT DO NOTHING;

INSERT INTO "Achievement" (
	"createdAt",
	"updatedAt",
	"name",
	"description",
	"picture"
)
VALUES (
	CURRENT_TIMESTAMP,
	CURRENT_TIMESTAMP,
	'Chi trova un amico, trova un tesoro',
	'You just added a new friend!',
	'https://www.eltekitalia.it/portal/wp-content/uploads/2023/12/psychedelic_cat_by_microdosediffusion_dfs4sg1-pre.png'
)
ON CONFLICT DO NOTHING;
